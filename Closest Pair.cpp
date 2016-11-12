//
//  main.cpp
//  Closest Pair
//
//  Created by Muhammad Rafay on 10/23/16.
//  Copyright © 2016 Muhammad Rafay. All rights reserved.
//  Algorithm to find the closest pair

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <float.h>
#include <iomanip>     

using namespace std;
int X1cordinate;
int Y1cordinate;

int X2cordinate;
int Y2cordinate;
struct ClosestPair {
    int x;
    int y;
};
// L2 Distance
double l2Distance(ClosestPair point1, ClosestPair point2)
{
    return sqrt( (pow((point1.x - point2.x),2)) +  pow( (point1.y - point2.y),2 ) ) ;
}
// Find closest pair in strip
double closestPairInStrip (ClosestPair middleStrip[],int N, double distance)
{
    double min = distance;
    for (int i=0; i<N; i++)
        for (int j = i+1; j < N && (middleStrip[j].y - middleStrip[i].y) < min; j++)
            if (l2Distance(middleStrip[i],middleStrip[j]) < min) {
                X1cordinate = middleStrip[i].x;
                Y1cordinate = middleStrip[i].y;
                X2cordinate = middleStrip[j].x;
                Y2cordinate = middleStrip[j].y;
                min = l2Distance(middleStrip[i], middleStrip[j]);
            }
    
    return min;
}

double bruteForce(ClosestPair points[], long N)
{
    double min = DBL_MAX; //Assign Maximum to variable float
    for (int i=0; i<N; i++)
        for (int j=i+1; j<N; j++)
            if (l2Distance(points[i], points[j]) < min) {
                X1cordinate = points[i].x;
                Y1cordinate = points[i].y;
                X2cordinate = points[j].x;
                Y2cordinate = points[j].y;
                min = l2Distance(points[i], points[j]);
            }
    return min;
}

double closestPoints(ClosestPair pointsX[], ClosestPair pointsY[], long N) {
    if (N <= 3)
        return bruteForce(pointsX,N);
    long mid = N/2;
    ClosestPair midPoint = pointsX[mid];
    ClosestPair pointYLeft[mid+1];
    ClosestPair pointYRight[N-mid-1];
    ClosestPair middleStrip[N];
    int leftIndex = 0, rightIndex = 0;
    
    for (int i=0; i<N; i++) {
        if (pointsY[i].x <= midPoint.x) {
            pointYLeft[leftIndex] = pointsY[i];
            leftIndex++;
        }
        else {
            pointYRight[rightIndex] = pointsY[i];
            rightIndex++;
        }
    }

    double leftResult = closestPoints(pointsX, pointYLeft, mid);
    double rightResult = closestPoints(pointsX+mid, pointYRight, N-mid);
    double minDistance = min(leftResult, rightResult);
    
    int pointsInMiddleStrip = 0;
    for (int i=0; i<N; i++)
        if (abs(pointsY[i].x - midPoint.x) < minDistance){
            middleStrip[pointsInMiddleStrip] = pointsY[i];
            pointsInMiddleStrip++;
        }
    
    return min(minDistance, closestPairInStrip(middleStrip,pointsInMiddleStrip,minDistance) );
}

int main(int argc, const char * argv[]) {
    vector < vector<int> > points;
    vector <int> cordinates;
    ifstream input("1000points.txt");
    
    // Storing the points in Vector
    if (input.is_open()) {
        while(!input.eof()) {
            int x, y;
            input>>x>>y;
            if(input.eof()) {
                break;
            }
            cordinates.push_back(x);
            cordinates.push_back(y);
            points.push_back(cordinates);
            cordinates.clear();
        }
    }
    //Declaring three Objects to find store cordinates
    ClosestPair Points[points.size()];  // Store all coridnate
    ClosestPair PointsX[points.size()]; // Cordinates sorted w.r.t to X
    ClosestPair PointsY[points.size()]; // Cordinates sorted w.r.t to Y

    // Copy the vector and make two vectors to sort
    vector< vector <int> > pointsX = points;
    vector< vector <int> > pointsY = points;
    // Sort pointsY vector according to Y cordinates
    sort(pointsY.begin(), pointsY.end(), [](const std::vector< int >& a, const std::vector< int >& b){ return a[1] < b[1]; } );
    
    // Sort pointsX vector according to Y cordinates
    sort(pointsX.begin(), pointsX.end(), [](const std::vector< int >& a, const std::vector< int >& b){ return a[0] < b[0]; } );

    // Store all cordinates in Points
    for (int i=0; i<points.size(); i++) {
        Points[i].x = points[i][0];
        Points[i].y = points[i][1];
    }
    
    // Store Sorted X and Y in PointsX and Points Y
    for (int i=0; i<points.size(); i++) {
        PointsX[i].x = pointsX[i][0];
        PointsX[i].y = pointsX[i][1];

        PointsY[i].x = pointsY[i][0];
        PointsY[i].y = pointsY[i][1];
    }
    cout << setprecision (9) << fixed;
    cout<< "The minimum distance is:"<<endl;
    cout<< closestPoints(PointsX, PointsY,pointsX.size())<<":"<<" ";
    cout<<"("<<X1cordinate<<", "<<Y1cordinate<<")";
    cout<<"<--->";
    cout<<"("<<X2cordinate<<", "<<Y2cordinate<<")";
    cout<<endl;

    return 0;
}
