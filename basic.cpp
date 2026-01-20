#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
//ctl
    if (argc == 2 && string(argv[1]) == "--help")
    {
        cout << "gufi --help" << endl;
        cout << "Usage:\n";
        cout << "  gfind ls   -la <path>\n";
        cout << "  gfind find -name <name>\n";
        cout << "  gfind find -size <value>\n";
        cout << "  gfind stat <file>\n";
        cout << "  gfind du   <path>\n";
        return 0;
    }

    if (argc < 2)
    {
        cerr << "Error: No command provided\n";
        return 1;
    }

    string cmnd = argv[1];

    if (cmnd == "find")
    {
        if (argc < 4)
        {
            cerr << "Error: Invalid find arguments\n";
            return 1;
        }

        int i = 2;                     // start AFTER "find"
        bool name_seen = false;
        bool size_seen = false;

        while (i < argc)
        {
            string option = argv[i];

            if (option != "-name" && option != "-size")
            {
                cerr << "Error: Invalid option '" << option << "'\n";
                return 1;
            }

            if (i + 1 >= argc)
            {
                cerr << "Error: Missing value for " << option << "\n";
                return 1;
            }

            if (option == "-name")
            {
                if (name_seen)
                {
                    cerr << "Error: -name specified more than once\n";
                    return 1;
                }
                name_seen = true;
            }

            if (option == "-size")
            {
                if (size_seen)
                {
                    cerr << "Error: -size specified more than once\n";
                    return 1;
                }
                size_seen = true;
            }

            i += 2;
        }

        /* ---- Build args for gufi_find ---- */
        char *args[argc + 1];

        args[0] = (char *)"gufi_find";
        args[1] = (char *)".";     // GUFI index

        int idx = 2;
        for (int j = 2; j < argc; j++)
        {
            args[idx++] = argv[j];
        }
        args[idx] = nullptr;

        execvp("gufi_find", args);
        perror("execvp failed");
        return 1;
    }

    /* ================= LS ================= */
    else if (cmnd == "ls")
    {
        execvp("ls", &argv[1]);
        perror("execvp failed");
        return 1;
    }

    /* ================= DU ================= */
    else if (cmnd == "du")
    {
        execvp("du", &argv[1]);
        perror("execvp failed");
        return 1;
    }

    /* ================= STAT ================= */
    else if (cmnd == "stat")
    {
        execvp("stat", &argv[1]);
        perror("execvp failed");
        return 1;
    }

    /* ================= INVALID ================= */
    else
    {
        cerr << "Error: Invalid command\n";
        return 1;
    }
}
