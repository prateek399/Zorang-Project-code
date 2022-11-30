#include <bits/stdc++.h>
#include <math.h>
using namespace std;
 


vector<vector<int>> solve(double longitude, double latitude, vector<vector<double>> add){
    
    set<vector<double>> s;
    // Assume longitude on the x-axis and latidude on the y-axis.
    // next we find the corresponding angles b/w x-axis and line formed by restaurant coordinates 
    // and each address coordinate respectively.

    for(int i=0;i<add.size();i++){
        double x=0, y=0, z=0, angle=0;
        x = add[i][0] - longitude; 
        y = add[i][1] - latitude;
        z = x/sqrt(x*x + y*y);
        angle = acosf(z);
        if(address[i][0] < longitude){
            angle *= -1;
        }
        s.insert({angle,add[i][0],add[i][1],sqrt(x*x + y*y), i+1});
    }

    // each address is kept int sorted order on the basis on angles achieved by using the
    // sorting in a set.

    vector<vector<double>> sorted_cords;

    for(auto it: s){
        sorted_cords.push_back({it[1],it[2],it[3],it[4]});
    }

    // Now, Apply binary search to get maximum time taken by delivery boys.

    int n =sorted_cords.size();
    double lo = 1;
    double hi = 1e9;
    double mid = (lo + hi)/2;
    vector<vector<int>> ret, ans1;
    while(hi - lo > 1e-6){
        int ans = 1e9;
        // finding min delivery boys required by assigning each address to a delivery boy one by one.
        for(int i=0;i<n;i++){
            ret.clear();
            vector<int> vis(n);
            int cnt = 0;
            for(int j=0; j<n; j++){ 
            // For a delivery boy, finding maximum address that he can deliever by iterating through addresses to order previously sorted
                int k = (j + i) % n;
                if(vis[k]) continue;
                ret.push_back({}); //empty vector
                ret[cnt].push_back(sorted_cords[k][3]);// storing address to delivery boy
                cnt++;
                vis[k] = 1;
                double x = sorted_cords[k][0];
                double y = sorted_cords[k][1];
                double dist = sorted_cords[k][2];
                
                if(2*dist > mid){ // comparing dtstance/time taken by a delievry boy to max time assumed
                    cnt = 11;
                    break;
                } 
                while(1){
                    k++; 
                    k %= n;
                    if(k == i) break;
                    if(vis[k]) continue;
                    double x1 = sorted_cords[k][0] - x;
                    double y1 = sorted_cords[k][1] - y;
                    double dist1 = sqrt(x1*x1+y1*y1);
                    double dist2 = sorted_cords[k][2];

                    if(dist1 + dist2 + dist <= mid){ // comparing dtstance/time taken by a delievry boy to max time assumed
                        dist+=dist1;
                        temp=dist2;
                        x = sorted_cords[k][0];
                        y = sorted_cords[k][1];
                        vis[k]=1; // marking the address visited if current delievery boy can visit under the assumed max time 
                        ret[cnt-1].push_back(sorted_cords[k][3]); // storing and assigning address to delievery boy
                    }
                }
            }
            ans = min(ans, cnt); // taking min delievery boys required till now for assumed max time
            if(ans <= 10) break;
        }
        
        if(ans <= 10){ // checking base conditions and changing the max time accordingly
            hi = mid;
            ans1 = ret;
        }
        else lo = mid + 1e-6;
        mid = (lo + hi)/2;
    }
    return ans1;
}
 
int main(){
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    double longitude, latitude;
    cin >> longitude >> latitude;
    vector<vector<double>>add;
    double x, y;
    int n; 
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> x >> y;
        add.push_back({x,y});
    }
    vector<vector<int>> ans=solve(longitude,latitude,add);
    for(int i=0; i<ans.size(); i++){
        for(int j=0; j<ans[i].size(); j++){
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
