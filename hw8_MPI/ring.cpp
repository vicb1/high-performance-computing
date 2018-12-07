#include <iostream>
#include <string>
#include <mpi.h>


int main(int argc, char *argv[]) {
    MPI::Init();
    int token = 0;
    size_t rounds = 1;
    if (argc >= 2) rounds = std::stol(argv[1]);

    int myrank = MPI::COMM_WORLD.Get_rank();
    int mysize = MPI::COMM_WORLD.Get_size();
    if (mysize < 4) {
        std::cout << "MPI::COMM_WORLD.Get_size() not large enough! " << std::endl;
        exit(-1);
    }
    while (rounds--) {
        if (0 == myrank) {
            std::cout << myrank << ": sending  " << token << std::endl;
            MPI::COMM_WORLD.Send(&token, 1, MPI::INT, 1, 321);
            MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, 3, 321);
            std::cout << myrank << ": received " << token << std::endl;
            ++token;
            // MPI::COMM_WORLD.Barrier();
        } else if (1 == myrank) {
            MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, 0, 321);
            std::cout << myrank << ": received " << token << std::endl;
            ++token;
            std::cout << myrank << ": sending  " << token << std::endl;
            MPI::COMM_WORLD.Send(&token, 1, MPI::INT, 2, 321);
            // MPI::COMM_WORLD.Barrier();
        } else if (2 == myrank) {
            MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, 1, 321);
            std::cout << myrank << ": received " << token << std::endl;
            ++token;
            std::cout << myrank << ": sending  " << token << std::endl;
            MPI::COMM_WORLD.Send(&token, 1, MPI::INT, 3, 321);
            // MPI::COMM_WORLD.Barrier();
        } else if (3 == myrank) {
            MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, 2, 321);
            std::cout << myrank << ": received " << token << std::endl;
            ++token;
            std::cout << myrank << ": sending  " << token << std::endl;
            MPI::COMM_WORLD.Send(&token, 1, MPI::INT, 0, 321);
            // MPI::COMM_WORLD.Barrier();
        } else {
            std::cout << "";
            // MPI::COMM_WORLD.Barrier();
            break;
        }
    }

    MPI::Finalize();

    return 0;
}
