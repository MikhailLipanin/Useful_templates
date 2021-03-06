    stack <int> stk;
    stk.push(0);
    vector <int> res;
    while (!stk.empty()){
        int v = stk.top();
        for (auto u : g[v]){
            if (can[v][u]) continue;
            can[v][u] = 1;
            stk.push(u);
            break;
        }
        if (v == stk.top()){
            res.pb(v);
            stk.pop();
        }
    }
    reverse(all(res));


////////////////////////////////////////////////////////////////////////////////
procedure FindEulerPath (V)
	1. перебрать все рёбра, выходящие из вершины V;
		каждое такое ребро удаляем из графа, и
		вызываем FindEulerPath из второго конца этого ребра;
	2. добавляем вершину V в ответ.
////////////////////////////////////////////////////////////////////////////////
stack St;
в St кладём любую вершину (стартовая вершина);
пока St не пустой
	пусть V - значение на вершине St;
	если степень(V) = 0, то
		добавляем V к ответу;
		снимаем V с вершины St;
	иначе
		находим любое ребро, выходящее из V;
		удаляем его из графа;
		второй конец этого ребра кладём в St;
