#include <pathfinder.h>
#include <vector>
#include <iostream>
int main(){
	
	//Number of trajectories
	int NUM_TRAJECTORIES = 4;
	int POINT_LENGTHS[NUM_TRAJECTORIES];

	//Number of waypoints in each trajectory
	POINT_LENGTHS[0] = 2;
	POINT_LENGTHS[1] = 3;
	POINT_LENGTHS[2] = 2;
	POINT_LENGTHS[3] = 2;

	double wheelbase_width = 2.1;

	std::vector<Segment*> left_trajectories = std::vector<Segment*>();
	std::vector<Segment*> right_trajectories = std::vector<Segment*>();
	
	int total_traj_length = 0;
	int traj_lengths[NUM_TRAJECTORIES];
	
	for (int i = 0; i < NUM_TRAJECTORIES; i++){
    		Waypoint *points = (Waypoint*)malloc(sizeof(Waypoint) * POINT_LENGTHS[i]);
		std::cout<<sizeof(Waypoint) * POINT_LENGTHS[i]<<std::endl;
		switch(i){
			case 0:
				points[0] = {0.0, 0.0, d2r(0.0)};
				points[1] = {0.01, 0.0, d2r(0.0)};
				break;
			//Fill cases with each trajectory. Number of cases = NUM_TRAJECTORIES
			case 1:
				points[0] = {0.0, 0.0, d2r(0.0)};
				points[1] = {-16.0, 0.0, d2r(0.0)};
				points[2] = {-23.6, 1.5, d2r(-25.0)};
				break;
			case 2:
				points[0] = {-23.6, 1.5, d2r(-25.0)};
				points[1] = {-17.6, 4.27, d2r(45.0)};
				break;
			case 3: 
    				points[0] = {-17.6, 4.27, d2r(45.0)};
				points[1] = {-23.6, 2.27, d2r(0.0)};
				break;
		}

		TrajectoryCandidate candidate;
  		pathfinder_prepare(points, POINT_LENGTHS[i], FIT_HERMITE_CUBIC, 					PATHFINDER_SAMPLES_FAST, 0.02, 17.0, 6.0, 100000.0, 						&candidate);

    		int length = candidate.length;
		traj_lengths[i] = length;
		total_traj_length += length;
std::cout<<length<<std::endl;		

    		Segment *trajectory = (Segment*)malloc(length * sizeof(Segment));
    
    		pathfinder_generate(&candidate, trajectory);
    	
    		Segment *leftTrajectory = (Segment*)malloc(sizeof(Segment) * length);
    		Segment *rightTrajectory = (Segment*)malloc(sizeof(Segment) * length);    	

    		pathfinder_modify_tank(trajectory, length, leftTrajectory, rightTrajectory, 						wheelbase_width);

		left_trajectories.push_back(leftTrajectory);
		right_trajectories.push_back(rightTrajectory);
	}
	
	Segment *leftTrajectory = (Segment*)malloc(sizeof(Segment) * total_traj_length);
    	Segment *rightTrajectory = (Segment*)malloc(sizeof(Segment) * total_traj_length);

	for (int i = 0; i<NUM_TRAJECTORIES; i++){
		unsigned int starting_pos = 0;
		for (unsigned int j = 0; j<i; j++){
			starting_pos += traj_lengths[j];
			//std::cout<<starting_pos<<std::endl;
		}
		for (unsigned int j = starting_pos; j<starting_pos + traj_lengths[i]; j++){
			Segment *left_ptr = leftTrajectory;
			Segment *right_ptr = rightTrajectory;
//std::cout<<left_ptr<< "    ";
			left_ptr += j;
			right_ptr += j;
//			std::cout<<left_ptr<<std::endl;
			*left_ptr = (left_trajectories.at(i)[j-starting_pos]);
			*right_ptr = (right_trajectories.at(i)[j-starting_pos]);
		}
	}
			
			
	
    	// Do something with the trajectories...

	FILE *fpl = fopen("trajectory_left.csv", "w");
	pathfinder_serialize_csv(fpl, leftTrajectory, total_traj_length);
	fclose(fpl);

	FILE *fpr = fopen("trajectory_right.csv", "w");
	pathfinder_serialize_csv(fpr, rightTrajectory, total_traj_length);
	fclose(fpr);

    	return 0;
}
