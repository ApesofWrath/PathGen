#include <pathfinder.h>
int main(){
	int POINT_LENGTH = 2;

    	Waypoint *points = (Waypoint*)malloc(sizeof(Waypoint) * POINT_LENGTH);

    	Waypoint p1 = { 0.0, 0.0, 0.0 };      // Waypoint @ x=-4, y=-1, exit angle=45 degrees
    	Waypoint p2 = { 5.0, 10.0, d2r(90.0) };             // Waypoint @ x=-1, y= 2, exit angle= 0 radians
    	//Waypoint p3 = {  2, 4, 0 };             // Waypoint @ x= 2, y= 4, exit angle= 0 radians
    	points[0] = p1;
    	points[1] = p2;
    	//points[2] = p3;
    
   	TrajectoryCandidate candidate;
  	pathfinder_prepare(points, POINT_LENGTH, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 0.05, 4.0, 10.0, 100000.0, &candidate);

    	int length = candidate.length;
    	Segment *trajectory = (Segment*)malloc(length * sizeof(Segment));
    
    	pathfinder_generate(&candidate, trajectory);
    
    	Segment *leftTrajectory = (Segment*)malloc(sizeof(Segment) * length);
    	Segment *rightTrajectory = (Segment*)malloc(sizeof(Segment) * length);
    
    	double wheelbase_width = 0.6;

    	pathfinder_modify_tank(trajectory, length, leftTrajectory, rightTrajectory, wheelbase_width);

    	// Do something with the trajectories...

	FILE *fp = fopen("trajectory.csv", "w");
	pathfinder_serialize_csv(fp, trajectory, length);
	fclose(fp);
    
    	free(trajectory);
    	return 0;
}
