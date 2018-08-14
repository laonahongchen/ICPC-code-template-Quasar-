Convex Polygon
//注意三点共线 
void ConvexPolygon(){
	sort(poi + 1, poi + n + 1);
	int stm = 0;
	for(int i = 1;i <= n;++i){
		while(stm > 1 && ((sta[stm] - sta[stm - 1]) ^ (poi[i] - sta[stm - 1])) <= 0)stm--;
		sta[++stm] = poi[i];
	}
	int tmp = stm;
	for(int i = n - 1;i > 0;--i){
		while(stm > tmp && ((sta[stm] - sta[stm - 1]) ^ (poi[i] - sta[stm - 1])) <= 0)stm--;
		sta[++stm] = poi[i];
	}
	if(n > 1)stm--;	
}
