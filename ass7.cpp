#include<iostream>
using namespace std;

const int P = 20;

const int R = 20;

int n, m;

void calculateNeed(int need[P][R], int maxm[P][R],
				int allot[P][R])
{
	for (int i = 0 ; i < n ; i++)
		for (int j = 0 ; j < m ; j++)
			need[i][j] = maxm[i][j] - allot[i][j];
}

bool isSafe(int processes[], int avail[], int maxm[][R],
			int allot[][R])
{
	int need[P][R];

	calculateNeed(need, maxm, allot);

	bool finish[P] = {0};

	int safeSeq[P];

	int work[R];
	for (int i = 0; i < m ; i++)
		work[i] = avail[i];

	int count = 0;
	while (count < n)
	{
		bool found = false;
		for (int p = 0; p < n; p++)
		{
			if (finish[p] == 0)
			{
				int j;
				for (j = 0; j < m; j++)
					if (need[p][j] > work[j])
						break;

				if (j == m)
				{
					for (int k = 0 ; k < m ; k++)
						work[k] += allot[p][k];

					safeSeq[count++] = p;

					finish[p] = 1;

					found = true;
				}
			}
		}

		if (found == false)
		{
			cout << "System is not in safe state\n";
			return false;
		}
	}

	cout << "System is in safe state.\nSafe"
		" sequence is: ";
	for (int i = 0; i < n ; i++)
		cout << "P" << safeSeq[i] << " ";
    cout << endl;
	return true;
}

void request(int avail[]) {
    cout << "Enter process: P";
    int p; cin >> p;
    int req[R];
    for (int i = 0; i < m; i++) {
        cout << "Enter resource value: ";
        cin >> req[i];
    }
    for (int i = 0; i < m; i++) {
        if (req[i] > avail[i]) {
            cout << "Request cannot be granted.\n";
            return;
        }
    }
    for (int i = 0; i < m; i++) {
        avail[i] -= req[i];
    }
    cout << "Request has been granted.\n";
}

void printMatrices(int need[P][R], int maxm[P][R], int allot[P][R], int avail[]) {
    bool done = false;
    cout << "Alloc\tAvail\tMaxm\tNeed\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << allot[i][j] << " ";
        }
        cout << "   ";
        for (int j = 0; j < m; j++) {
            cout << maxm[i][j] << " ";
        }
        cout << "   ";
        for (int j = 0; j < m; j++) {
            cout << need[i][j] << " ";
        }
        cout << "   ";
        if (!done) {
            for (int j = 0; j < m; j++) {
                cout << avail[j] << " ";
            }
            cout << "   ";
            done = true;
        }
        cout << endl;
    }
}

int main()
{
    cout << "Enter number of processes: ";
    cin >> n;
    int processes[P];
    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    cout << "Enter number of resource types: ";
    cin >> m; 
    int avail[R];
    cout << "Enter instances of resources:\n";
    for (int i = 0; i < m; i++) {
        cout << "Enter available resource type: ";
        int x; cin >> x;
        avail[i] = x;
    }
  
    cout << "Enter values for max matrix:\n";
    int maxm[P][R];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "Enter value: ";
            int x; cin >> x;
            maxm[i][j] = x;
        }
    }
    
    int allot[P][R];
    cout << "Enter values for allocation matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "Enter value: ";
            int x; cin >> x;
            allot[i][j] = x;
        }
    }
  
    // isSafe(processes, avail, maxm, allot);

    int ch = 0;
    while (1) {
        cout << "1. Calculate need. 2. Check Safety 3. Accept Request 4. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            int need[P][R];
            calculateNeed(need, maxm, allot);
            printMatrices(need, maxm, allot, avail);
            break;
        
        case 2:
            isSafe(processes, avail, maxm, allot);
            break;

        case 3:
            request(avail);
            printMatrices(need, maxm, allot, avail);
            break;

        case 4:
            exit(0);

        default:
            cout << "Enter valid choice.\n";
            break;
        }
    }
  
    return 0;
}
