#include "formangradientvector.h"
#include "edge_collapse.cpp"
#include "Timer.h"

#define PIGRECO 3.1415927
#define THRESHOLDNORM 0.0001


void FormanGradientVector::simplify(bool output_model, char *nome_file)
{

    list<DAG_TopoNode *> tot_topo_sempl;
    list<DAG_GeomNode *> tot_geom_sempl;
    dag_per_vertex = new vector<DAG_GeomNode *>(mesh->getNumVertex(), NULL);
    //assert(valid_gradient());

    map<int, nNode *> *minima_nodes = new map<int, nNode *>();
    map<pair<int, int>, iNode *> *saddle_nodes = new map<pair<int, int>, iNode *>();
    map<int, nNode *> *maxima_nodes = new map<int, nNode *>();

    compute_critical_simplexes(minima_nodes, saddle_nodes, maxima_nodes);
    pair<double, double> pers = compute_incidence_graph(minima_nodes, saddle_nodes, maxima_nodes);

    Timer time_geom;
    Timer time_topo;

    double tot_geom = 0.0;
    double tot_topo = 0.0;

    bool val = true;
    while (val)
    {
        cout << "Inizio Geom" << endl;
        time_geom.start();
        list<DAG_GeomNode *> *geom_it = simplify_geometry(dag_per_vertex);
        tot_geom_sempl.insert(tot_geom_sempl.begin(), geom_it->begin(), geom_it->end());
        //assert(valid_gradient());
        time_geom.stop();
        tot_geom += time_geom.getElapsedTime();

        cout << "Inizio Topo" << endl;
        time_topo.start();
        list<DAG_TopoNode *> *topo_it = simplify_persistence(&min_map, &saddle_map, &max_map);
        tot_topo_sempl.insert(tot_topo_sempl.begin(), topo_it->begin(), topo_it->end());
        time_topo.stop();
        tot_topo += time_topo.getElapsedTime();

        //assert(valid_gradient());
        val = ((topo_it->size() > 0) || geom_it->size() > 0);
        delete topo_it;
        delete geom_it;
    }

    cout << "Tempo per le semplificazioni " << endl;
    cout << "-topologiche: " << tot_topo << endl;
    cout << "-geometriche: " << tot_geom << endl;
    cout << "Geom Simpl" << tot_geom_sempl.size() << endl;
    cout << "Topo Simpl" << tot_topo_sempl.size() << endl;
    reorder_forman_gradient();
    geom_root = *(mesh->reorder_triangulation(&tot_geom_sempl, dag_per_vertex)); //qui costruisco gia' anche la gerarchia geometrica
    set_alive_simplexes();
    build_topo_hierarchy(&tot_topo_sempl, &min_map, &saddle_map, &max_map);

    delete minima_nodes;
    delete saddle_nodes;
    delete maxima_nodes;

    this->tot_geom = tot_geom_sempl.size();
    this->tot_topo = tot_topo_sempl.size();

    cout << "in RADICE " << topo_root.size() << " " << geom_root.size() << endl;

    if (output_model)
    {

        output_mm(&tot_topo_sempl, &tot_geom_sempl, nome_file);
    }
}

void FormanGradientVector::build_topo_hierarchy(list<DAG_TopoNode *> *dag_nodes, map<Node *, DAG_TopoNode *> *min_map, map<Node *, DAG_TopoNode *> *saddle_map, map<Node *, DAG_TopoNode *> *max_map)
{

    for (list<DAG_TopoNode *>::iterator it = dag_nodes->begin(); it != dag_nodes->end(); it++)
    {

        list<nNode *> maxima = (*it)->getMaximaList();
        list<iNode *> saddle = (*it)->getSaddleList();
        list<nNode *> minima = (*it)->getMinimaList();

        bool in_root = true;
        for (list<nNode *>::iterator it2 = maxima.begin(); it2 != maxima.end(); it2++)
        {
            map<Node *, DAG_TopoNode *>::iterator it3 = max_map->find(*it2);
            if (it3 != max_map->end())
            {
                (*it3).second->add_child(*it);
                (*it)->add_father((*it3).second);
                in_root = false;
            }
        }

        for (list<iNode *>::iterator it2 = saddle.begin(); it2 != saddle.end(); it2++)
        {
            map<Node *, DAG_TopoNode *>::iterator it3 = saddle_map->find(*it2);
            if (it3 != saddle_map->end())
            {
                (*it3).second->add_child(*it);
                (*it)->add_father((*it3).second);
                in_root = false;
            }
        }

        for (list<nNode *>::iterator it2 = minima.begin(); it2 != minima.end(); it2++)
        {
            map<Node *, DAG_TopoNode *>::iterator it3 = min_map->find(*it2);
            if (it3 != min_map->end())
            {
                (*it3).second->add_child(*it);
                (*it)->add_father((*it3).second);
                in_root = false;
            }
        }

        if (in_root)
            topo_root.push_front(*it);

        //qui connect with geometry stuff
        vector<int> vertices = (*it)->getVertices();
        set<int> vert_no_rep(vertices.begin(), vertices.end());
        for (set<int>::iterator it2 = vert_no_rep.begin(); it2 != vert_no_rep.end(); it2++)
        {
            //assert(*it2 < dag_per_vertex->size());
            if ((*dag_per_vertex)[*it2] != NULL)
            {
                (*it)->add_geom((*dag_per_vertex)[*it2]);
            }
        }
    }
}

void FormanGradientVector::build_persistence_queue(priority_queue<Topo_Sempl *, vector<Topo_Sempl *>, sort_arcs_topo> *queue)
{

    for (int i = 0; i < 2; i++)
    {
        set<Arc *> arcs = forman_ig.getLevelArcs(i);
        for (set<Arc *>::iterator it = arcs.begin(); it != arcs.end(); it++)
        {
            if ((*it)->getLabel() == 1)
            {
                double val;
                int index_ex;
                Edge *critical_edge = NULL;
                vector<int> filt_ex;
                if (i == 1)
                {
                    //val = euclidean_distance((*it)->getNode_i()->getCriticalIndex(), mesh->getTopSimplexHighestVertex((*it)->getNode_j()->getCriticalIndex()));

                    pair<int, int> critical_edge_tetra = ((iNode *)((*it))->getNode_i())->get_edge_id();

                    if (critical_edge_tetra.second < 0)
                    { //Only one side
                        critical_edge = mesh->getTopSimplex(critical_edge_tetra.first).TE(-critical_edge_tetra.second - 1);
                    }
                    else
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (!(mesh->getTopSimplex(critical_edge_tetra.second).contains(mesh->getTopSimplex(critical_edge_tetra.first).TV(i))))
                            {
                                critical_edge = mesh->getTopSimplex(critical_edge_tetra.first).TE(i);
                                break;
                            }
                        }
                    }

                    int index_i = ((*it))->getNode_i()->getCriticalIndex();
                    index_ex = mesh->getTopSimplexHighestVertex(((*it))->getNode_j()->getCriticalIndex());
                    val = abs(field[index_i] - field[index_ex]);

                    Triangle t = mesh->getTopSimplex(((*it))->getNode_j()->getCriticalIndex());
                    for (int i = 0; i < 3; i++)
                        filt_ex.push_back(filtration[t.TV(i)]);
                    sort(filt_ex.begin(), filt_ex.end(), greater<int>());
                }
                else
                {

                    pair<int, int> critical_edge_tetra = ((iNode *)((*it))->getNode_j())->get_edge_id();

                    if (critical_edge_tetra.second < 0)
                    { //Only one side
                        critical_edge = mesh->getTopSimplex(critical_edge_tetra.first).TE(-critical_edge_tetra.second - 1);
                    }
                    else
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (!(mesh->getTopSimplex(critical_edge_tetra.second).contains(mesh->getTopSimplex(critical_edge_tetra.first).TV(i))))
                            {
                                critical_edge = mesh->getTopSimplex(critical_edge_tetra.first).TE(i);
                                break;
                            }
                        }
                    }

                    index_ex = ((*it))->getNode_i()->getCriticalIndex();
                    int index_j = ((*it))->getNode_j()->getCriticalIndex();
                    //val = euclidean_distance((*it)->getNode_i()->getCriticalIndex(), (*it)->getNode_j()->getCriticalIndex());
                    val = abs(field[index_j] - field[index_ex]);
                    filt_ex.push_back(filtration[index_ex]);
                }
                int filt0 = (filtration[critical_edge->EV(0)] > filtration[critical_edge->EV(1)]) ? filtration[critical_edge->EV(0)] : filtration[critical_edge->EV(1)];
                int filt1 = (filtration[critical_edge->EV(0)] > filtration[critical_edge->EV(1)]) ? filtration[critical_edge->EV(1)] : filtration[critical_edge->EV(0)];

                queue->push(new Topo_Sempl(*it, val, i, filt0, filt1, filt_ex));
            }
        }
    }
    cout << "============FINISHED BUILD QUEUE=============" << endl;
}

list<DAG_TopoNode *> *FormanGradientVector::simplify_persistence(map<Node *, DAG_TopoNode *> *min_map, map<Node *, DAG_TopoNode *> *saddle_map, map<Node *, DAG_TopoNode *> *max_map)
{

    //sulla base dell'incidence graph calcolato semplifico i critici.
    //devo trovare una relazione bloccante sulla base della quale ricominciare con la geometria
    //es. un delta di controllo sulla differenza in valore scalare fra due simplessi da semplificare.

    //prepare queue degli ordini di persistenza.
    //
    cout << "Inizio una sessione di semplificazioni" << endl;
    priority_queue<Topo_Sempl *, vector<Topo_Sempl *>, sort_arcs_topo> *queue = new priority_queue<Topo_Sempl *, vector<Topo_Sempl *>, sort_arcs_topo>();
    build_persistence_queue(queue);
    DAG_TopoNode *dagnode;

    list<DAG_TopoNode *> *ordered_topo = new list<DAG_TopoNode *>();

    Topo_Sempl *sempl;
    iNode *saddle = NULL;
    nNode *extrema = NULL;
    while ((!queue->empty() /*&& queue->top()->val <= pers_limit*/))
    {

        sempl = queue->top();
        queue->pop();

        if (sempl->arc->getLabel() != 1)
        {
            if (sempl->arc->getLabel() == -1)
                delete sempl->arc;

            delete sempl;
            continue;
        }

        if (sempl->lvl == 0)
        {
            saddle = sempl->arc->getNode_j();
            extrema = sempl->arc->getNode_i();

            if (saddle->getArcs(true).size() != 2)
                continue;
            dagnode = contraction_mr(extrema, saddle, queue);
            if (dagnode != NULL)
            {
                //assert(saddle!=NULL);
                (*min_map)[extrema] = dagnode;
                (*saddle_map)[saddle] = dagnode;
                dagnode->setHeight(sempl->val);
                ordered_topo->push_front(dagnode);
            }
        }
        else
        {
            saddle = sempl->arc->getNode_i();
            extrema = sempl->arc->getNode_j();

            if (saddle->getArcs(false).size() != 2)
                continue;
            dagnode = removal_mr(extrema, saddle, queue);
            if (dagnode != NULL)
            {
                //assert(saddle!=NULL);
                (*max_map)[extrema] = dagnode;
                (*saddle_map)[saddle] = dagnode;
                dagnode->setHeight(sempl->val);
                ordered_topo->push_front(dagnode);
            }
        }
        delete sempl;
        //        compute_incidence_graph();
        //        writeVTK_IG("ultima_iterazione.vtk");
    }

    delete queue;

    return ordered_topo;
}

void FormanGradientVector::simplify_geometry(bool QEM_setting, double limit)
{
    int done = 0;
    priority_queue<Geom_Sempl *, vector<Geom_Sempl *>, sort_arcs_geom> *queue = new priority_queue<Geom_Sempl *, vector<Geom_Sempl *>, sort_arcs_geom>();
    QEM_based = QEM_setting;
    vector<bool> visited;
    // vector<bool> visited_vertex;
    vector<Matrix> initialQuadric;
    vector<vector<double>> trianglePlane;

    vector<int> e;
    bool delete_all = false;
    if (limit < 0)
        delete_all = true;

    Timer timer;
    timer.start();

    if (QEM_based == true)
    {
        cout << "=========Calculate triangle plane========" << endl;
        trianglePlane = vector<vector<double>>(mesh->getTopSimplexesNum(), vector<double>(4, 0));
        mesh->computeTrianglesPlane(&trianglePlane);
        cout << "=========Calculate initial QEM========" << endl;
        initialQuadric = vector<Matrix>(mesh->getNumVertex(), Matrix(0.0));
        mesh->computeInitialQEM(&initialQuadric, &trianglePlane);
        vector<vector<double>>().swap(trianglePlane);
    }
    timer.stop();
    cout << "       - time building QEM:      " << timer.getElapsedTime() << endl;

    cerr << "[MEMORY] peak for computing QEM: " << to_string(MemoryUsage().get_Virtual_Memory_in_MB()) << " MBs" << std::endl;
    timer.start();
    while (true)
    {
        map<vector<int>, double> values;
        visited = vector<bool>(mesh->getTopSimplexesNum(), false);
        //visited_vertex = vector<bool>(mesh->getNumVertex(), false);
        int t_count = 0;
        for (int i = 0; i < mesh->getTopSimplexesNum(); i++)
        {
            visited[i] = true;
            if (!mesh->is_alive(i))
                continue;
            t_count++;
            for (int j = 0; j < 3; j++)
            {
                if ((mesh->getTopSimplex(i).TT(j) != -1 && visited[mesh->getTopSimplex(i).TT(j)]))
                {
                    continue;
                }
                Edge edge = mesh->getTopSimplex(i).TE_new(j);
                if ((getVE_new(edge.EV(0)) == -1) && (getVE_new(edge.EV(1)) == -1))
                {
                   // delete edge;
                }
                else
                {
                    vector<double> new_vertex();
                    double value;
                    if (QEM_based == true)
                    {
                        e = {edge.EV(0), edge.EV(1)};
                        sort(e.begin(), e.end());
                        int new_vertex_pos = -1;
                        value = mesh->compute_error(e[0], e[1], &initialQuadric, new_vertex_pos);
                        assert(new_vertex_pos != -1);
                        if (new_vertex_pos == 1)
                        {
                            int tmp = e[1];
                            e[1] = e[0];
                            e[0] = tmp;
                        }

                        map<vector<int>, double>::iterator it = values.find(e);
                        if (it == values.end())
                        {
                            values[e] = value;
                            if (delete_all)
                            {
           //                     cout<<"["<<e[0]<<","<< e[1]<<"]  Error will be introduced: "<<value<<endl;
                                Edge *insert_edge = new Edge(e[0], e[1]);
                              //  Vertex3D v = mesh->getVertex(e[0]);
                                //    new_vertex={v.getX(),v.getY(),v.getZ()};
                                queue->push(new Geom_Sempl(insert_edge, value));
                            }
                            else
                            {
                                if ((value - limit) < SMALL_TOLER)
                                {
                                    //     cout<<"["<<e[0]<<","<< e[1]<<"]  Error will be introduced: "<<value<<endl;
                                    Edge *insert_edge = new Edge(e[0], e[1]);
                              //      Vertex3D v = mesh->getVertex(e[0]);
                                    //    new_vertex={v.getX(),v.getY(),v.getZ()};
                                    queue->push(new Geom_Sempl(insert_edge, value));
                                }
                            }
                        }
                    }
                    else
                    {
                        e = {edge.EV(0), edge.EV(1)};
                        sort(e.begin(), e.end());
                        Vertex3D v1 = mesh->getVertex(e[0]);
                        Vertex3D v2 = mesh->getVertex(e[1]);
                        map<vector<int>, double>::iterator it = values.find(e);
                        if (it == values.end())
                        {
                            //    { new_vertex[0] = v1.getX(); new_vertex[1] = v1.getY(), new_vertex[2] = v1.getZ(); }
                            vector<double> dif = {v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ()};
                            value = sqrt(dif[0] * dif[0] + dif[1] * dif[1] + dif[2] * dif[2]);
                            //  cout<<"["<<e[0]<<","<<e[1]<<"]  Edge length: "<<value<<endl;

                            values[e] = value;
                            if (delete_all)
                            {
                                Edge *insert_edge = new Edge(e[0], e[1]);
                                queue->push(new Geom_Sempl(insert_edge, value));
                            }
                            else
                            {
                                if (value + SMALL_TOLER<limit)
                                {
                                    Edge *insert_edge = new Edge(e[0], e[1]);
                                    queue->push(new Geom_Sempl(insert_edge, value));
                                    //cout<<"ENQUEUE"<<endl;
                                }
                            }
                        }
                    }
                    //delete edge;
                }
            }
        }
        
        values.clear();
        vector<bool>().swap(visited);
        cout << "number of remaining triangles:" << t_count << endl;
        int done_new = 0;
        
     //   vector<int> vv;
        cout << "**** [Number] " << queue->size() << " edges enqueued. Start simplification.****" << endl;
        cerr << "[MEMORY] peak for finding edges: " << to_string(MemoryUsage().get_Virtual_Memory_in_MB()) << " MBs" << std::endl;

        while (!queue->empty())
        {
            vector<int> et;
            Geom_Sempl *sempl = queue->top();
            Edge *edge = sempl->edge;
            double qem_value = sempl->val;
            //vector<double> new_v = sempl->new_v;
            queue->pop();
            delete sempl;
            vector<int> sorted_e = {edge->EV(0), edge->EV(1)};
            sort(sorted_e.begin(), sorted_e.end());
            auto it = updated_edges.find(sorted_e);

            if (it != updated_edges.end())
            {

                if (fabs(it->second - qem_value) > SMALL_TOLER)
                {
                    //   cout<<"[DEBUG] edge: "<<sorted_e[0]<<", "<<sorted_e[1]<<"; updated error: "<<it->second<<"old error: "<<qem_value<<endl;
                    delete edge;
                    continue;
                }
            }
            if (!mesh->is_v_alive(edge->EV(0)) || !mesh->is_v_alive(edge->EV(1)))
            {
                //    cout<<"[DEBUG] edge not complete: "<<edge->EV(0)<<", "<<edge->EV(1)<<endl;
                delete edge;
                continue;
            }

            int paired_v = getVE_new(edge->EV(0));
            
            int v1, v2;
            v1 = v2 = -1;
            bool v1_pair_e = false;
            if (paired_v != -1 && paired_v ==edge->EV(1) )
            {
                v1_pair_e = true;
            }

            //One gradient check condition
            // if(e1 != NULL && *e1 == *edge){//v1 is paired with current edge
            //     v2 = edge->EV(0);
            //     v1 = edge->EV(1);// exchange v1 and v2, ensure the pair is deleted together
            //     cout<<"v1 is paired with current edge"<<endl;
            //     delete e1;
            // }
            // else{
            //     delete e1;
            //     e1 = getVE(edge->EV(1)); //v2 is paired with current edge.
            //     if(e1 != NULL && *e1 == *edge){
            //         cout<<"v2 is paired with current edge"<<endl;
            //         v2 = edge->EV(1);
            //         v1 = edge->EV(0); //v2 and the edge should be removed together.
            //     }
            //     else{
            //         cout<<"Edge "<<edge->EV(0)<<", "<<edge->EV(1)<<" cannot be removed"<<endl;
            //         cout<<"v1/v2 should be paired with edge"<<endl;
            //     }
            //     delete e1;
            // }
            v2 = edge->EV(1);
            v1 = edge->EV(0);
            if (v1 != -1)
            {
                int t1, t2;
                et = mesh->ET(*edge);
                //  cout<<"Checking edge "<<v1+1<<", "<<v2+1<<endl;
                if (et.size() == 0)
                {
                    //     cout<<"Edge("<<v1<<", "<<v2<<") ET size is zero"<<endl;
                    delete edge;
                    continue;
                }
                else if (et.size() == 1)
                {
                    //  cout<<v1<<" and "<<v2<<" are ignored due to no triangles"<<endl;
                    delete edge;
                    continue;
                }
                else
                {
                    t1 = et[0];
                    t2 = et[1];
                }

                vector<int> vt1;
                vector<int> vt2;
                vt1 = mesh->VT(v1);
                vt2 = mesh->VT(v2);
                if (/*!visited_vertex[v2] &&*/ mesh->link_condition(v1, v2, t1, t2) && not_fold_over(v1, v2, vt1, vt2)&& valid_gradient_configuration(v1, v2, t1, t2, vt1, vt2) /*&& mesh->convex_neighborhood(v1,v2,t1,t2) &&*/)
                {
                    if (QEM_based == true)
                    {
                        mesh->half_edge_collapse_QEM(v1, v2, t1, t2, queue, limit, &initialQuadric, &trianglePlane, updated_edges);
                    }
                    else
                    {
                        mesh->half_edge_collapse_simple(v1, v2, t1, t2, queue, limit);
                    }

                    // if(v1_pair_e&&v2_vtstar!=t1&&v2_vtstar!=t2){
                    //   mesh->getVertex(v1).VTstar(v2_vtstar);
                    //   }
                    TriGradient grad;
                    vt1 = mesh->VT(v1);
                    for (int j = 0; j < vt1.size(); j++)
                    {
                        if (vt1[j] == t1 || vt1[j] == t2)
                            continue;
                        grad = convert_compressed_to_expand(forman_gradient[vt1[j]]);
                        if (!grad.is_vertex_unpaired(mesh->getTopSimplex(vt1[j]).vertex_index(v1)))
                        {
                            mesh->getVertex(v1).VTstar(vt1[j]);
                            break;
                        }
                    }

                    done_new++;
                }
            }

            delete edge;
        }
        updated_edges.clear();
        if (done_new == 0)
            break;
        done += done_new;
        cout << "Simplified edge number in THIS ROUND:" << done_new << endl;
        cerr << "[MEMORY] peak for simplification: " << to_string(MemoryUsage().get_Virtual_Memory_in_MB()) << " MBs" << std::endl;

        //change_vtstar_mesh();
    }
    delete queue;
    timer.stop();
    cout << "       - time simplification:      " << timer.getElapsedTime() << endl;

    cout << "Simplified edge number: " << done << endl;

    reorder_forman_gradient();
    mesh->reorder_triangulation();
    set_alive_simplexes();
    change_vtstar_mesh();
}

list<DAG_GeomNode *> *FormanGradientVector::simplify_geometry(vector<DAG_GeomNode *> *dag_per_vertex)
{

    int done = 0;
    priority_queue<Geom_Sempl_old *, vector<Geom_Sempl_old *>, sort_arcs_geom_old> *queue = new priority_queue<Geom_Sempl_old *, vector<Geom_Sempl_old *>, sort_arcs_geom_old>();
    list<DAG_GeomNode *> *performed_simpl = new list<DAG_GeomNode *>();
    QEM_based = true;

    double edg_lenght = -1;
    vector<bool> visited;
    vector<bool> visited_vertex;
    vector<Matrix> initialQuadric;
    if (QEM_based == true)
    {
        cout << "inizio i piani " << endl;

        vector<vector<double>> trianglePlane = vector<vector<double>>(mesh->getTopSimplexesNum(), vector<double>(4, 0));
        mesh->computeTrianglesPlane(&trianglePlane);

        cout << "piani costruiti " << endl;

        initialQuadric = vector<Matrix>(mesh->getNumVertex(), Matrix(0.0));
        mesh->computeInitialQEM(&initialQuadric, &trianglePlane);

        cout << "setup finito " << endl;
    }
    while (true)
    {

        visited = vector<bool>(mesh->getTopSimplexesNum(), false);
        visited_vertex = vector<bool>(mesh->getNumVertex(), false);

        for (int i = 0; i < mesh->getTopSimplexesNum(); i++)
        {
            visited[i] = true;
            if (!mesh->is_alive(i))
                continue;
            for (int j = 0; j < 3; j++)
            {
                if (mesh->getTopSimplex(i).TT(j) != -1 && !visited[mesh->getTopSimplex(i).TT(j)] && mesh->is_alive(i) && mesh->is_alive(mesh->getTopSimplex(i).TT(j)))
                {
                    Edge *edge = mesh->getTopSimplex(i).TE(j);
                    //                    if(getEF(edge) != -1){
                    //                        delete edge;
                    //                        continue;
                    //                    }
                    if (getVE(edge->EV(0)) != NULL)
                    { //v1 is not critical
                        vector<double> new_vertex(3, 0);

                        double error = mesh->compute_error(edge->EV(0), edge->EV(1), &initialQuadric, &new_vertex);
                        queue->push(new Geom_Sempl_old(edge, error, new_vertex));
                    }
                    else if (getVE(edge->EV(1)) != NULL)
                    { //v2 is not critical
                        vector<double> new_vertex(3, 0);

                        double error = mesh->compute_error(edge->EV(0), edge->EV(1), &initialQuadric, &new_vertex);
                        queue->push(new Geom_Sempl_old(edge, error, new_vertex));
                    }
                    else
                    {
                        delete edge;
                    }
                }
            }
        }

        int done_new = 0;
        vector<int> et;
        vector<int> vv;
        while (!queue->empty())
        {

            Geom_Sempl_old *sempl = queue->top();
            Edge *edge = sempl->edge;
            double qem_value = sempl->val;
            vector<double> new_v = sempl->new_v;
            queue->pop();
            delete sempl;

            if (!mesh->is_v_alive(edge->EV(0)) || !mesh->is_v_alive(edge->EV(1)))
            {
                delete edge;
                continue;
            }

            Edge *e1 = getVE(edge->EV(0));
            int v1, v2;
            v1 = v2 = -1;

            if (e1 != NULL && *e1 == *edge)
            { //v1 is paired with current edge
                v2 = edge->EV(0);
                v1 = edge->EV(1); // exchange v1 and v2, ensure the pair is deleted together
                delete e1;
            }
            else
            {
                delete e1;
                e1 = getVE(edge->EV(1)); //v2 is paired with current edge.
                if (e1 != NULL && *e1 == *edge)
                {
                    v2 = edge->EV(1);
                    v1 = edge->EV(0); //v2 and the edge should be removed together.
                }
                delete e1;
            }

            if (v1 != -1)
            {

                int t1, t2;
                et = mesh->ET(*edge);
                if (et.size() < 2)
                {
                    delete edge;
                    continue;
                }
                t1 = et[0];
                t2 = et[1];

                //assert(t1 > -1 && t2 > -1);
                bool to_switch_sin, to_switch_des;
                to_switch_des = to_switch_sin = false;

                if (!visited_vertex[v2] && mesh->link_condition(v1, v2, t1, t2) /*&& mesh->convex_neighborhood(v1,v2,t1,t2) &&*/
                    && valid_gradient_configuration(v1, v2, t1, t2, &to_switch_sin, &to_switch_des))
                {

                    DAG_GeomNode *dagnode = mesh->half_edge_collapse(v1, v2, t1, t2, new_v);
                    if (dagnode != NULL)
                    {
                        edg_lenght = qem_value;
                        initialQuadric[v1] = initialQuadric[v1] + initialQuadric[v2];
                        done_new++;
                        dagnode->set_edge_lenght(edg_lenght);
                        dagnode->set_to_switch(to_switch_sin, to_switch_des);

                        (*dag_per_vertex)[v2] = dagnode;

                        performed_simpl->push_front(dagnode);
                        vv = mesh->VV(v1);
                        for (int k = 0; k < vv.size(); k++)
                        {
                            visited_vertex[vv[k]] = true;
                        }
                    }
                }
            }

            delete edge;
        }

        if (done_new == 0)
            break;
        done += done_new;
    }

    cout << "Total simplification geom" << done << endl;
    //   cout << "Greater Edge Lenght " << edg_lenght << endl;

    return performed_simpl;
}

bool FormanGradientVector::valid_gradient_configuration(int v1, int v2, int t1, int t2, bool *to_switch_sin, bool *to_switch_des)
{
    //assert(mesh->is_v_alive(v1) && mesh->is_v_alive(v2));
    //assert(mesh->is_alive(t1) && mesh->is_alive(t2));
    //assert(mesh->getTopSimplex(t1).contains(v1) && mesh->getTopSimplex(t1).contains(v2));
    //assert(mesh->getTopSimplex(t2).contains(v1) && mesh->getTopSimplex(t2).contains(v2));

    vector<int> vt1 = mesh->VT(v1);
    vector<int> vt = mesh->VT(v2);
    if (mesh->isBoundary(v2) || mesh->isBoundary(v1))
    {
        //cout<<"border edge"<<endl;
        return false;
    }
    if (vt.size() < 4 || vt1.size() < 4)
    {
        //cout<<"less than 4 triangles"<<endl;
        return false;
    }
    if (is_face_critical(t1) || is_face_critical(t2))
    {
        cout << "t1 or t2 is critical" << endl;
        return false;
    }
    int v3_sin, v3_des;
    v3_sin = v3_des = -1;

    //aggiunti ora
    for (int i = 0; i < vt.size(); i++)
    {
        if (is_face_critical(vt[i]))
        {
            //  cout<<"[DEBUG]"<<vt[i]<<endl;
            //  cout<<"vt2 is critical"<<endl;
            return false;
        }
    }

    for (int i = 0; i < vt1.size(); i++)
    {
        if (is_face_critical(vt1[i]))
        {
            //  cout<<"vt1 is critical"<<endl;
            return false;
        }
    }

    vector<int> vv = mesh->VV(v2);
    for (int i = 0; i < vv.size(); i++)
    {
        if (is_edge_critical(vv[i], v2))
        {
            //   cout<<"vv(v2) has critical edge"<<endl;
            return false;
        }
    }

    //su t1
    for (int i = 0; i < 3; i++)
    {
        if (mesh->getTopSimplex(t1).TV(i) != v1 && mesh->getTopSimplex(t1).TV(i) != v2)
        {
            v3_sin = mesh->getTopSimplex(t1).TV(i);
            break;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (mesh->getTopSimplex(t2).TV(i) != v1 && mesh->getTopSimplex(t2).TV(i) != v2)
        {
            v3_des = mesh->getTopSimplex(t2).TV(i);
            break;
        }
    }

    if (is_edge_critical(v1, v2) ||
        is_edge_critical(v2, v3_sin) ||
        is_edge_critical(v2, v3_des) ||
        is_edge_critical(v1, v3_des) ||
        is_edge_critical(v1, v3_sin))
    {
        //   cout<<"edge is critical"<<endl;
        return false;
    }
    //Why need this?
    // if(getVE(v3_sin) != NULL && getVE(v3_sin)->EV(1) == v2) {cout<<"v3 sin pair is v2"<<endl;return false;}
    // if(getVE(v3_des) != NULL && getVE(v3_des)->EV(1) == v2) {cout<<"v3 des pair is v2"<<endl;return false;}

    if (is_vertex_critical(v2))
    {
        //  cout<<"v2 is critical"<<endl;
        return false;
    }
    //assert(*getVE(v2) == Edge(v1,v2));

    Edge *edge1 = getVE(v3_sin);

    Edge *edge2 = getVE(v1);

    Edge *edge3 = getVE(v2);
    if (edge2 == NULL || edge3 == NULL)
    {
        //  cout<<"edge is not paired with v1 or v2"<<endl;
        return false;
    }
    if (edge2->EV(1) != v2 && edge3->EV(1) != v1)
    {
        //   cout<<"edge is not paired with v1 or v2"<<endl;
        return false;
    }
    if (edge1 != NULL && *edge1 == Edge(v3_sin, v2))
    {

        //  cout<<"v3_sin is paired with v2"<<endl;
        //devo fare l'update sul triangolo sotto t1
        int t3 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v2));

        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v1));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v1));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
    }
    else if (edge1 != NULL && *edge1 == Edge(v3_sin, v1))
    {
        //     cout<<"v3_sin is paired with v1"<<endl;
        //devo fare l'update sul triangolo sopra t2
        int t3 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v1));

        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v2));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v2));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
    }
    else if (edge2 != NULL && *edge2 == Edge(v3_sin, v1))
    {
        //   cout<<"v1 is paired with v3_sin"<<endl;
        //   cout<<"v1:"<<v1<<" v3_sin:"<<v3_sin<<endl;
        //devo fare l'update sul triangolo sopra t2
        int t3 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v1));

        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v2), mesh->getTopSimplex(t3).vertex_index(v3_sin));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v2), mesh->getTopSimplex(t3).vertex_index(v3_sin));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
    }
    else if (edge2 != NULL && *edge2 == Edge(v1, v2) && edge3 != NULL && *edge3 == Edge(v2, v3_sin))
    {
        int t3 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v2));

        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v1));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v1), mesh->getTopSimplex(t3).vertex_index(v3_sin));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
    }

    delete edge1;
    //lato destro
    edge1 = getVE(v3_des);
    if (edge1 != NULL && *edge1 == Edge(v3_des, v2))
    {
        //      cout<<"v3_des is paired with v2"<<endl;
        //devo fare l'update sul triangolo sotto t2
        int t3 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v2));

        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v1));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v1));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());

        *to_switch_des = true;
    }
    else if (edge1 != NULL && *edge1 == Edge(v3_des, v1))
    {
        //  cout<<"v3_des is paired with v1"<<endl;
        // cout<<"v1:"<<v1<<" v3_des:"<<v3_des<<endl;
        //devo fare l'update sul triangolo sopra t2
        int t3 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v1));

        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v2));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v2));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
    }
    else if (edge2 != NULL && *edge2 == Edge(v3_des, v1))
    {
        //    cout<<"v1 is paired with v3_des"<<endl;
        //devo fare l'update sul triangolo sopra t2
        int t3 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v1));

        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v2), mesh->getTopSimplex(t3).vertex_index(v3_des));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v2), mesh->getTopSimplex(t3).vertex_index(v3_des));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
    }
    else if (edge2 != NULL && *edge2 == Edge(v1, v2) && edge3 != NULL && *edge3 == Edge(v2, v3_des))
    {
        int t3 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v2));

        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v1));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v1), mesh->getTopSimplex(t3).vertex_index(v3_des));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
    }

    delete edge1;
    delete edge2;
    delete edge3;

    return true;
}

/// v2 is the vertex to be removed
bool FormanGradientVector::valid_gradient_configuration(int v1, int v2, int t1, int t2, vector<int> &vt, vector<int> &vt1)
{
    //assert(mesh->is_v_alive(v1) && mesh->is_v_alive(v2));
    //assert(mesh->is_alive(t1) && mesh->is_alive(t2));
    //assert(mesh->getTopSimplex(t1).contains(v1) && mesh->getTopSimplex(t1).contains(v2));
    //assert(mesh->getTopSimplex(t2).contains(v1) && mesh->getTopSimplex(t2).contains(v2));
    // cout<<"[debug]checking edge "<<v1<<", "<<v2<<endl;
    // vt = mesh->VT(v1);
    // vt1 = mesh->VT(v2);
    if (mesh->isBoundary(v2) || mesh->isBoundary(v1))
    {
        //     cout<<"border edge"<<endl;
        return false;
    }
    if (vt.size() < 4 || vt1.size() < 4)
    {
        //    cout<<"less than 4 triangles"<<endl;
        return false;
    }
    if (is_face_critical(t1) || is_face_critical(t2))
    {
        //   cout<<"t1 or t2 is critical"<<endl;
        return false;
    }
    int v3_sin, v3_des;
    v3_sin = v3_des = -1;

    //aggiunti ora
    // for (int i = 0; i < vt.size(); i++)
    // {
    //     if (is_face_critical(vt[i]))
    //     {

    //         return false;
    //     }
    // }

    for(int i=0; i<vt1.size(); i++){
        if(is_face_critical(vt1[i])) {
     //        cout<<"vt1 is critical"<<endl;
            return false;}
    }

    vector<int> vv = mesh->VV(v2);
    for (int i = 0; i < vv.size(); i++)
    {
        if (is_edge_critical(vv[i], v2))
        {

            return false;
        }
    }

    //su t1
    for (int i = 0; i < 3; i++)
    {
        if (mesh->getTopSimplex(t1).TV(i) != v1 && mesh->getTopSimplex(t1).TV(i) != v2)
        {
            v3_sin = mesh->getTopSimplex(t1).TV(i);
            break;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (mesh->getTopSimplex(t2).TV(i) != v1 && mesh->getTopSimplex(t2).TV(i) != v2)
        {
            v3_des = mesh->getTopSimplex(t2).TV(i);
            break;
        }
    }

    if (is_edge_critical(v1, v2) ||
        is_edge_critical(v2, v3_sin) ||
        is_edge_critical(v2, v3_des) ||
        is_edge_critical(v1, v3_des) ||
        is_edge_critical(v1, v3_sin))
    {
        //   cout<<"edge is critical"<<endl;
        return false;
    }
    //Why need this?
    // if(getVE(v3_sin) != NULL && getVE(v3_sin)->EV(1) == v2) {return false;}
    // if(getVE(v3_des) != NULL && getVE(v3_des)->EV(1) == v2) {return false;}

    if (is_vertex_critical(v2))
    {
        //         cout<<"v2 is critical"<<endl;
        return false;
    }
    //assert(*getVE(v2) == Edge(v1,v2));

    int pair_e1 = getVE_new(v3_sin);

    int pair_e2 = getVE_new(v1);

    int pair_e3 = getVE_new(v2);
    if (pair_e2 == -1 && pair_e3 != -1 && pair_e3!= v1)
    {
        // when v1 is critical, and the edge is not paired with v2
        //       cout<<"edge is not paired with v1 or v2"<<endl;
        return false;
    }
    else if (pair_e2 != -1 && pair_e2 != v2 && pair_e3 != -1 && pair_e3 != v1)
    {
        // when v1 is not critical, and both vertices are not paired with e. 
        
        //  cout<<"v1: "<<v1<<" v1_pair: "<<edge2->EV(1)<<endl;
        //  cout<<"v2: "<<v2<<" v2_pair: "<<edge3->EV(1)<<endl;
        //   cout<<"edge is not paired with v1 or v2"<<endl;
        return false;
    }
    if (pair_e1 != -1 && pair_e1 ==  v2)
    {

        // cout<<"v3_sin is paired with v2"<<endl;
        //devo fare l'update sul triangolo sotto t1
        int t3 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v2));
        int t4 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v1));
        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v1));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v1));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
      //  mesh->getVertex(v3_sin).VTstar(t4);
    }
    else if (pair_e1 != -1 && pair_e1 ==  v1)
    {
        // cout<<"v3_sin is paired with v1"<<endl;
        //devo fare l'update sul triangolo sopra t2
        int t3 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v1));
        int t4 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v2));
        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v2));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v2));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
    //    mesh->getVertex(v3_sin).VTstar(t4);
    }
    else if (pair_e2 != -1 && pair_e2 ==  v3_sin)
    {
        // cout<<"v1 is paired with v3_sin"<<endl;
        //  cout<<"v1:"<<v1<<" v3_sin:"<<v3_sin<<endl;
        //devo fare l'update sul triangolo sopra t2
        int t3 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v1));
        //    int t4 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v2));
        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v2), mesh->getTopSimplex(t3).vertex_index(v3_sin));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v2), mesh->getTopSimplex(t3).vertex_index(v3_sin));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
        //    mesh->getVertex(v1).VTstar(t4);
    }
    else if (pair_e2 != -1 && pair_e2 == v2 && pair_e3 != -1 && pair_e3 == v3_sin)
    {
        int t3 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v2));
        int t4 = mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v1));
        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_sin), mesh->getTopSimplex(t3).vertex_index(v1));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v1), mesh->getTopSimplex(t3).vertex_index(v3_sin));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
     //   mesh->getVertex(v2).VTstar(t4);
    }
    if (mesh->getVertex(v3_sin).VTstar() == t1)
        mesh->getVertex(v3_sin).VTstar(mesh->getTopSimplex(t1).TT(mesh->getTopSimplex(t1).vertex_index(v1)));
  
    //lato destro
    pair_e1 = getVE_new(v3_des);
    if (pair_e1 != -1 && pair_e1 ==  v2)
    {
        // cout<<"v3_des is paired with v2"<<endl;
        //devo fare l'update sul triangolo sotto t2
        int t3 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v2));
        int t4 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v1));
        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v1));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v1));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
      //  mesh->getVertex(v3_des).VTstar(t4);
    }
    else if (pair_e1 != -1 && pair_e1 ==  v1)
    {
        // cout<<"v3_des is paired with v1"<<endl;
        // cout<<"v1:"<<v1<<" v3_des:"<<v3_des<<endl;
        //devo fare l'update sul triangolo sopra t2
        int t3 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v1));
        int t4 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v2));
        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v2));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v2));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
     //   mesh->getVertex(v3_des).VTstar(t4);
    }
    else if (pair_e2 != -1 && pair_e2 ==  v3_des)
    {
        // cout<<"v1 is paired with v3_des"<<endl;
        //devo fare l'update sul triangolo sopra t2
        int t3 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v1));
        //   int t4 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v2));
        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v2), mesh->getTopSimplex(t3).vertex_index(v3_des));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v2), mesh->getTopSimplex(t3).vertex_index(v3_des));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
        //  mesh->getVertex(v1).VTstar(t4);
    }
    else if (pair_e2 != -1 && pair_e2 == v2 && pair_e3 != -1 && pair_e3 ==  v3_des)
    {
        int t3 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v2));
        int t4 = mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v1));
        TriGradient grad = convert_compressed_to_expand(forman_gradient[t3]);
        grad.erase_edge_relation(mesh->getTopSimplex(t3).vertex_index(v3_des), mesh->getTopSimplex(t3).vertex_index(v1));
        grad.setVE(mesh->getTopSimplex(t3).vertex_index(v1), mesh->getTopSimplex(t3).vertex_index(v3_des));
        forman_gradient[t3] = convert_expand_to_compressed(grad.getArrow());
     //   mesh->getVertex(v2).VTstar(t4);
    }
    if (mesh->getVertex(v3_des).VTstar() == t2)
        mesh->getVertex(v3_des).VTstar(mesh->getTopSimplex(t2).TT(mesh->getTopSimplex(t2).vertex_index(v2)));
    // delete edge1;
    // delete edge2;
    // delete edge3;

    return true;
}

DAG_TopoNode *FormanGradientVector::contraction_mr(nNode *extrema, iNode *saddle, priority_queue<Topo_Sempl *, vector<Topo_Sempl *>, sort_arcs_topo> *queue)
{

    vector<Arc *> arcs = saddle->getArcs(true);
    //assert(arcs.size() == 2);
    nNode *other_extrema;
    int vertex, next_vertex;
    int ending_path_simplex, label_p1;

    //assert(arcs[1]->getSimplexj() != arcs[0]->getSimplexj());
    int ex_minimum = extrema->getCriticalIndex();
    pair<int, int> ex_saddle;

    pair<int, int> critical_edge_tetra = saddle->get_edge_id();
    Edge *critical_edge = NULL;
    if (critical_edge_tetra.second < 0)
    {
        critical_edge = mesh->getTopSimplex(critical_edge_tetra.first).TE(-critical_edge_tetra.second - 1);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if (!(mesh->getTopSimplex(critical_edge_tetra.second).contains(mesh->getTopSimplex(critical_edge_tetra.first).TV(i))))
            {
                critical_edge = mesh->getTopSimplex(critical_edge_tetra.first).TE(i);
                break;
            }
        }
    }
    //assert(critical_edge != NULL);
    ex_saddle = pair<int, int>(critical_edge->EV(0), critical_edge->EV(1));

    //assert(is_vertex_critical(ex_minimum));
    //assert(is_edge_critical(ex_saddle.first,ex_saddle.second));

    //SETUP per dopo
    if (arcs[0]->getNode_i() == extrema)
    {
        other_extrema = (nNode *)arcs[1]->getNode_i();
        next_vertex = mesh->getTopSimplex(saddle->get_edge_id().first).TV(arcs[0]->getSimplexj());
        vertex = mesh->getTopSimplex(saddle->get_edge_id().first).TV(arcs[1]->getSimplexj());
        ending_path_simplex = arcs[1]->getSimplexi();
        label_p1 = arcs[1]->getLabel();
    }
    else
    {
        other_extrema = (nNode *)arcs[0]->getNode_i();
        next_vertex = mesh->getTopSimplex(saddle->get_edge_id().first).TV(arcs[1]->getSimplexj());
        vertex = mesh->getTopSimplex(saddle->get_edge_id().first).TV(arcs[0]->getSimplexj());
        ending_path_simplex = arcs[0]->getSimplexi();
        label_p1 = arcs[0]->getLabel();
    }
    //assert(extrema != other_extrema);
    //assert(extrema->getCriticalIndex() != other_extrema->getCriticalIndex());
    Edge *old_edge = critical_edge;

    //modifiche sul gradiente
    while (next_vertex != ex_minimum)
    {

        //trovo il nuovo edge;
        Edge *edge = getVE(next_vertex);
        //assert(edge != NULL);
        vertex = next_vertex;
        edge->EV(0) == vertex ? next_vertex = edge->EV(1) : next_vertex = edge->EV(0);

        //azzero la sua adiacenza;
        freeVE(vertex, next_vertex);

        //accoppio il vecchio edge;
        if (old_edge->EV(0) == vertex)
        {
            setVE(old_edge->EV(0), old_edge->EV(1));
        }
        else
        {
            setVE(old_edge->EV(1), old_edge->EV(0));
        }

        delete old_edge;
        old_edge = edge;
    }
    //assert(next_vertex == ex_minimum);
    setVE(next_vertex, vertex);

    //modifiche sul IG
    arcs[0]->setLabel(-1);
    arcs[1]->setLabel(-1);
    list<nNode *> to_q;
    list<int> label_to_q;
    vector<Arc *> maxima_arcs = saddle->getArcs(false);
    nNode *maxima;
    for (int i = 0; i < maxima_arcs.size(); i++)
    {
        label_to_q.push_back(maxima_arcs[i]->getLabel());
        to_q.push_back((nNode *)maxima_arcs[i]->getNode_j());

        maxima_arcs[i]->setLabel(-1);
        maxima = ((nNode *)maxima_arcs[i]->getNode_j());

        forman_ig.removeArc(1, maxima_arcs[i]);
        maxima->removeArc(maxima_arcs[i]);
        saddle->removeArc(false, maxima_arcs[i]);
    }

    list<iNode *> to_p;
    list<int> label_to_p;
    vector<Arc *> saddle_arcs = extrema->getArcs();
    iNode *node_saddle1 = NULL;
    for (int i = 0; i < saddle_arcs.size(); i++)
    {

        label_to_p.push_back(saddle_arcs[i]->getLabel()); //per il DAG
        saddle_arcs[i]->setLabel(-1);
        int starting_index = saddle_arcs[i]->getSimplexj();

        node_saddle1 = ((iNode *)saddle_arcs[i]->getNode_j()); //per il DAG

        //        //QUESTO SOLO PER DEBUG
        //        Edge* critical_edge2=NULL;
        //        critical_edge_tetra = node_saddle1->get_edge_id();
        //        if(critical_edge_tetra.second<0){
        //            critical_edge2 = mesh->getTopSimplex(critical_edge_tetra.first).TE(-critical_edge_tetra.second-1);
        //        }
        //        else{
        //            for(int i=0; i<3; i++){
        //                if(!(mesh->getTopSimplex(critical_edge_tetra.second).contains(mesh->getTopSimplex(critical_edge_tetra.first).TV(i)))){
        //                    critical_edge2 = mesh->getTopSimplex(critical_edge_tetra.first).TE(i);
        //                    break;
        //                }
        //            }
        //        }
        //        //assert(critical_edge2 != NULL);
        //        //-----------------------------------------------------------

        forman_ig.removeArc(0, saddle_arcs[i]);
        node_saddle1->removeArc(true, saddle_arcs[i]);
        extrema->removeArc(saddle_arcs[i]);

        if (node_saddle1 != saddle)
        {
            //assert(is_edge_critical(critical_edge2->EV(0), critical_edge2->EV(1)));

            to_p.push_back(node_saddle1);
            if (forman_ig.already_connected(other_extrema, node_saddle1) == NULL)
            {
                Arc *arco = forman_ig.addArc(other_extrema, ending_path_simplex, node_saddle1, starting_index, 0);

                if (arco->getLabel() == 1)
                {
                    double val = abs(field[arco->getNode_i()->getCriticalIndex()] - field[arco->getNode_j()->getCriticalIndex()]);
                    //queue->push(new Topo_Sempl(arco, val, 0));
                }
                //assert(node_saddle1->getArcs(true).size() <= 2);
            }
            else
            {
                forman_ig.already_connected(other_extrema, node_saddle1)->setLabel(2);
                Arc *arco = forman_ig.addArc(other_extrema, ending_path_simplex, node_saddle1, starting_index, 0);
                arco->setLabel(2);
                //assert(node_saddle1->getArcs(true).size() == 2);
            }
        }
        else
        {
            label_to_p.pop_back();
        }
    }

    vector<Arc *> minima_arcs = saddle->getArcs(true);
    nNode *minima;
    for (int i = 0; i < minima_arcs.size(); i++)
    {
        minima_arcs[i]->setLabel(-1);
        minima = ((nNode *)minima_arcs[i]->getNode_i());

        forman_ig.removeArc(0, minima_arcs[i]);
        minima->removeArc(minima_arcs[i]);
        saddle->removeArc(true, minima_arcs[i]);
    }

    forman_ig.removeNode(saddle, 1);
    forman_ig.removeNode(extrema, 0);
    vector<int> vertice(1);
    vertice[0] = ex_minimum;

    DAG_TopoNode *nodedag = new DAG_TopoNode(extrema, saddle, other_extrema, to_p, to_q, label_to_p, label_to_q, label_p1, true, vertice, ex_saddle, next_vertex);
    return nodedag;
}

DAG_TopoNode *FormanGradientVector::removal_mr(nNode *extrema, iNode *saddle, priority_queue<Topo_Sempl *, vector<Topo_Sempl *>, sort_arcs_topo> *queue)
{

    vector<Arc *> arcs = saddle->getArcs(false);
    //assert(arcs.size() == 2);
    nNode *other_extrema;
    int triangle;
    int vertex = -1;
    int ending_path_simplex;

    int triang_crit = extrema->getCriticalIndex();

    //assert(arcs[1]->getSimplexi() != arcs[0]->getSimplexi());
    int label_p1; //per DAG;

    if (arcs[0]->getNode_j() == extrema)
    {
        other_extrema = (nNode *)arcs[1]->getNode_j();
        triangle = arcs[0]->getSimplexi();
        ending_path_simplex = arcs[1]->getSimplexj();
        label_p1 = arcs[1]->getLabel();
    }
    else
    {
        other_extrema = (nNode *)arcs[0]->getNode_j();
        triangle = arcs[1]->getSimplexi();
        ending_path_simplex = arcs[0]->getSimplexj();
        label_p1 = arcs[0]->getLabel();
    }

    //assert(saddle->get_edge_id().first==triangle || saddle->get_edge_id().second==triangle);

    Edge *old_edge = NULL;
    Edge *edge = NULL;
    pair<int, int> twotriangles = saddle->get_edge_id();
    if (twotriangles.second >= 0)
    {
        for (int j = 0; j < 3; j++)
        {
            if (twotriangles.second == mesh->getTopSimplex(twotriangles.first).TT(j))
            {
                old_edge = mesh->getTopSimplex(twotriangles.first).TE(j);
                break;
            }
        }
    }
    else
    {
        old_edge = mesh->getTopSimplex(twotriangles.first).TE(-twotriangles.second - 1);
    }
    //assert(old_edge != NULL);
    //assert(is_edge_critical(old_edge->EV(0), old_edge->EV(1)));

    //assert(is_face_critical(triang_crit));
    pair<int, int> critical_edge(old_edge->EV(0), old_edge->EV(1)); //per DAG

    //modifiche sul gradiente
    int next_triangle = triangle;

    while (!is_face_critical(next_triangle))
    {

        //trovo il nuovo edge;
        int i = 0;
        for (; i < 3; i++)
        {
            edge = mesh->getTopSimplex(next_triangle).TE(i);
            int tri = getEF(edge);
            if (tri == next_triangle)
                break;
            delete edge;
        }
        //assert(i<3);

        triangle = next_triangle;
        next_triangle = mesh->getTopSimplex(triangle).TT(i);
        vertex = mesh->getTopSimplex(triangle).TV(i);

        //azzero la sua adiacenza;
        //assert(mesh->is_alive(triangle));
        //assert(mesh->getTopSimplex(triangle).contains(vertex));
        freeEF(vertex, triangle);

        //accoppio il vecchio edge;
        for (int i = 0; i < 3; i++)
        {
            if (old_edge->EV(0) != mesh->getTopSimplex(triangle).TV(i) &&
                old_edge->EV(1) != mesh->getTopSimplex(triangle).TV(i))
            {
                vertex = mesh->getTopSimplex(triangle).TV(i);
                break;
            }
        }
        setEF(vertex, triangle);

        delete old_edge;
        old_edge = edge;
    }

    //assert(next_triangle == triang_crit);

    for (int i = 0; i < 3; i++)
    {
        if (old_edge->EV(0) != mesh->getTopSimplex(next_triangle).TV(i) &&
            old_edge->EV(1) != mesh->getTopSimplex(next_triangle).TV(i))
        {
            vertex = mesh->getTopSimplex(next_triangle).TV(i);
            break;
        }
    }
    //assert(i<3);
    setEF(vertex, next_triangle);
    int start_vertex = vertex;

    //modifiche sul IG (aggiustare situazioni qui!!!!)
    arcs[0]->setLabel(-1);
    arcs[1]->setLabel(-1);

    list<nNode *> to_q;   //per DAG;
    list<int> label_to_q; //per DAG;
    vector<Arc *> minima_arcs = saddle->getArcs(true);
    nNode *minima;
    for (int i = 0; i < minima_arcs.size(); i++)
    {
        label_to_q.push_back(minima_arcs[i]->getLabel()); //per DAG;
        minima_arcs[i]->setLabel(-1);
        minima = ((nNode *)minima_arcs[i]->getNode_i());

        to_q.push_back(minima); //per DAG;
        forman_ig.removeArc(0, minima_arcs[i]);
        minima->removeArc(minima_arcs[i]);
        saddle->removeArc(true, minima_arcs[i]);
    }

    list<iNode *> to_p;   //per DAG;
    list<int> label_to_p; //per DAG;
    vector<Arc *> saddle_arcs = extrema->getArcs();
    iNode *node_saddle1 = NULL;
    for (int i = 0; i < saddle_arcs.size(); i++)
    {

        node_saddle1 = ((iNode *)saddle_arcs[i]->getNode_i());

        if (node_saddle1 != saddle)
        {

            label_to_p.push_back(saddle_arcs[i]->getLabel()); //per DAG;
            saddle_arcs[i]->setLabel(-1);
            int starting_path_simplex = saddle_arcs[i]->getSimplexi();
            forman_ig.removeArc(1, saddle_arcs[i]);
            node_saddle1->removeArc(false, saddle_arcs[i]);
            extrema->removeArc(saddle_arcs[i]);

            //            //QUI PER DEBUG
            //            pair<int,int> triang= ((iNode*)saddle_arcs[i]->getNode_i())->get_edge_id();
            //            Edge* crit=NULL;
            //            if(triang.second >= 0){
            //                for(int j=0; j<3;j++){
            //                    if(triang.second == mesh->getTopSimplex(triang.first).TT(j)){
            //                        crit = mesh->getTopSimplex(triang.first).TE(j);
            //                        break;
            //                    }
            //                }
            //            }
            //            else{
            //                crit = mesh->getTopSimplex(triang.first).TE(-triang.second -1);
            //            }
            //            //assert(crit !=NULL);
            //            //cout << crit->EV(0) << " " << crit->EV(1) << endl;
            //            //assert(is_edge_critical(crit->EV(0), crit->EV(1)));
            //            //--------------------------

            to_p.push_back(node_saddle1); //per DAG;
            if (forman_ig.already_connected(other_extrema, node_saddle1) == NULL)
            {
                Arc *arco = forman_ig.addArc(node_saddle1, starting_path_simplex, other_extrema, ending_path_simplex, 1);
                if (arco->getLabel() == 1)
                {
                    double val = abs(field[arco->getNode_i()->getCriticalIndex()] - field[mesh->getTopSimplexHighestVertex(arco->getNode_j()->getCriticalIndex())]);
                    //queue->push(new Topo_Sempl(arco, val, 1));
                }
                //assert(node_saddle1->getArcs(false).size() <= 2);
            }
            else
            {
                forman_ig.already_connected(other_extrema, node_saddle1)->setLabel(2);
                //                Arc* arco = forman_ig.addArc(node_saddle1, starting_path_simplex, other_extrema, ending_path_simplex, 1);
                //                arco->setLabel(2);
                //                //assert(node_saddle1->getArcs(false).size() == 2);
            }
        }
        //        else{
        //            label_to_p.pop_back(); //per DAG;
        //        }
    }

    vector<Arc *> maxima_arcs = saddle->getArcs(false);
    //assert(maxima_arcs.size()==2);
    nNode *maxima;
    for (int i = 0; i < maxima_arcs.size(); i++)
    {
        maxima_arcs[i]->setLabel(-1);
        maxima = ((nNode *)maxima_arcs[i]->getNode_j());

        forman_ig.removeArc(1, maxima_arcs[i]);
        maxima->removeArc(maxima_arcs[i]);
        saddle->removeArc(false, maxima_arcs[i]);
    }

    vector<int> triang(3);
    triang[0] = mesh->getTopSimplex(triang_crit).TV(0);
    triang[1] = mesh->getTopSimplex(triang_crit).TV(1);
    triang[2] = mesh->getTopSimplex(triang_crit).TV(2);

    forman_ig.removeNode(saddle, 1);
    forman_ig.removeNode(extrema, 2);

    //cout << "ho ucciso " << triang_crit << " con:" << critical_edge.first << "," << critical_edge.second << endl;

    DAG_TopoNode *nodedag = new DAG_TopoNode(extrema, saddle, other_extrema, to_p, to_q, label_to_p, label_to_q, label_p1, false, triang, critical_edge, start_vertex);
    return nodedag;
}

bool FormanGradientVector::not_fold_over(int v1, int v2, vector<int> vt1, vector<int> vt2)
{

    sort(vt1.begin(), vt1.end());
    sort(vt2.begin(), vt2.end());

    vector<int> vt2_sub_et;
    // cout<<"v1: "<<v1<<endl;
    // cout<<"v2: "<<v2<<endl;
    set_difference(vt2.begin(), vt2.end(), vt1.begin(), vt1.end(), std::back_inserter(vt2_sub_et));
    // cout<<"vt1 size:"<<vt1.size()<<endl;
    // cout<<"vt2 size:"<<vt2.size()<<endl;
    //     cout<<"vt1: ";
    //     for(int i=0;i<vt1.size();i++){
    //         cout<<vt1[i]<<",";
    //     }
    //     cout<<endl;

    //     cout<<"vt2: ";
    //     for(int i=0;i<vt2.size();i++){
    //         cout<<vt2[i]<<",";
    //     }
    //     cout<<endl;

    // cout<<"vt2-et: ";
    for (int i = 0; i < vt2_sub_et.size(); i++)
    {
        // cout<<vt2_sub_et[i]<<",";
        if (!mesh->is_alive(vt2_sub_et[i]))
            continue;
        Triangle t = mesh->getTopSimplex(vt2_sub_et[i]);
        int v2_pos = t.vertex_index(v2);
        Edge e = t.TE_new(v2_pos);
        bool same_side = same_side_of_edge(v1, v2, e.EV(0), e.EV(1));
        //    cout<<"edge:"<<v1<<", "<<v2<<endl;
        // cout<<"result:"<<same_side<<endl;
        if (!same_side)
            return false;
    }
    // cout<<endl;
    return true;
}