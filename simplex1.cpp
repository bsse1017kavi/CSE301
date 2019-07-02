#include<bits/stdc++.h>
using namespace std;

int getMinimum(double *arr,int len)
{
    double min=INT_MAX,ind=0;

    for(int i=0;i<len;i++)
    {
        if(arr[i]<min)
        {
            min = arr[i];
            ind = i;
        }
    }

    return ind;

}

bool is_optimized(double *arr,int len)
{
    for(int i=0;i<len;i++)
    {
        if(arr[i]<0)
        {
            return false;
        }
    }

    return true;
}

int countVar(string s)
{
    int count = 0;

    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='x')
        {
            count++;
        }
    }

    return count;
}


vector<string> split(const string& s, string seperator)
{
   vector<string> output;

   int len = seperator.length();

    int prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos+len-1, pos-prev_pos)); // Last word

    return output;
}

void updateObjectiveFunc(double *objCoeff,string objFunc)
{
        vector<string> splits = split(objFunc,"=");

        double val;
        int index;

        splits = split(splits[1],"+");

        for(vector<string> :: iterator it = splits.begin();it!=splits.end();it++)
        {
             string temp1 = "",temp2 = "";
            bool chk = false;

            string current = (*it);

            for(int j=0;j<current.length();j++)
            {
                if(current[j]=='_')
                {
                    chk = true;
                }

                if(current[j]=='_'||current[j]=='x')
                {
                    continue;
                }

                if(!chk)
                {
                    temp1+=current[j];
                }

                else
                {
                    temp2+=current[j];
                }
            }


            istringstream iss1(temp1),iss2(temp2);
            int coeff,index;
            iss1 >> coeff;
            iss2 >> index;

            index--;

            objCoeff[index] = coeff;
        }
}

void updateConstrainCoeff(double **constrainCoeff,string constrain[],int m,int n)
{
    for(int i=0;i<m;i++)
    {
        vector<string> splits = split(constrain[i],"<=");

        double val;

        istringstream iss(splits[1]);

        iss >> val;

        constrainCoeff[i][n] = val;

        splits = split(splits[0],"+");

        for(vector<string> :: iterator it = splits.begin();it!=splits.end();it++)
        {
            //cout << (*it) << "\t";

            string temp1 = "",temp2 = "";
            bool chk = false;

            string current = (*it);

            for(int j=0;j<current.length();j++)
            {
                if(current[j]=='_')
                {
                    chk = true;
                }

                if(current[j]=='_'||current[j]=='x')
                {
                    continue;
                }

                if(!chk)
                {
                    temp1+=current[j];
                }

                else
                {
                    temp2+=current[j];
                }
            }


            istringstream iss1(temp1),iss2(temp2);
            int coeff,index;
            iss1 >> coeff;
            iss2 >> index;

            index--;

            constrainCoeff[i][index] = coeff;
        }

        //cout << endl;
    }
}

void print_table(double **table,int row,int column)
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            cout << table[i][j] << "\t";
        }

        cout << endl;
    }
}

int main(void)
{
    int m;

    cin >> m;

    string faltu;

    getline(cin,faltu);

    string constrains[m];

    for(int i=0;i<m;i++)
    {
        getline(cin,constrains[i]);
    }

    string objfunc;

    getline(cin,objfunc);

    int n = countVar(objfunc);

    //cout << n << endl;

    double **coeffOfConstrains = new double*[m];
    double *objCoeff = new double[n];

    for(int i=0;i<m;i++)
    {
        coeffOfConstrains[i] = new double[n+1];
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            coeffOfConstrains[i][j] = 0;
        }
    }

    //print_table(coeffOfConstrains,m,n);

    updateConstrainCoeff(coeffOfConstrains,constrains,m,n);
    updateObjectiveFunc(objCoeff,objfunc);

    //print_table(coeffOfConstrains,m,n+1);

    /*for(int i=0;i<n;i++)
    {
        cout << objCoeff[i] << " ";
    }*/

    double **table = new double*[m+1];

    for(int i=0;i<m+1;i++)
    {
        table[i] = new double[n+m+1];
    }

    for(int i=0;i<m+1;i++)
    {
        for(int j=0;j<n+m+1;j++)
        {
            table[i][j] = 0;
        }
    }

    //cout << endl;

    //Initialization
    for(int i=0;i<m+1;i++)
    {
        for(int j=0;j<n+m+1;j++)
        {
            if(i==0 && j>n-1 && j<n+m)table[i][j] = 0;

            else if(i==0 && j<=n-1)
            {
                table[i][j] = (-1)*objCoeff[j];
            }

            if(i>0 && j<=n-1)
            {
                table[i][j] = coeffOfConstrains[i-1][j];
            }

            else if(i>0 && j>n-1 && j<n+m)
            {
                table[i][n+i-1] = 1;
            }

            else if(i>0 && j==n+m)
            {
                table[i][j] = coeffOfConstrains[i-1][n];
            }
        }
    }

    cout << endl;

    print_table(table,m+1,n+m+1);

    int k=0;
    while(true)
    {
        int pivotColumn = getMinimum(table[0],n+m+1);
        double *ratio = new double[m];
        for(int i=1;i<m+1;i++)
        {
            ratio[i-1] = table[i][n+m]/table[i][pivotColumn];
        }

        int pivotRow = getMinimum(ratio,m)+1;

        double pivot = table[pivotRow][pivotColumn];

        for(int j=0;j<n+m+1;j++)
        {
            table[pivotRow][j]/= pivot;
        }

        for(int i=0;i<m+1;i++)
        {
            if(i==pivotRow) continue;

            double pivotElement = table[i][pivotColumn];

            for(int j=0;j<n+m+1;j++)
            {
                double oldVal = table[i][j];
                double newVal = oldVal - pivotElement*table[pivotRow][j];
                table[i][j] = newVal;
            }
        }

        //cout << pivotRow << endl;

        cout << endl;

        print_table(table,m+1,n+m+1);

        if(is_optimized(table[0],n+m+1))
        {
        	cout << "Ohh" << endl;
        	break;
        }

        k++;
    }

    cout << endl;

    //print_table(table,m+1,n+m+1);

}
