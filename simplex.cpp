/*#include <iostream>
#include<string.h>
#include <sstream>
#include <math.h>*/
#include<bits/stdc++.h>

using namespace std;

string formatEquation(string objectiveFunction)
 {
    string temp = "";

    for (int i = 0; i < objectiveFunction.length() - 1; i++)
    {
        if ((objectiveFunction[i] == 'x' || objectiveFunction[i] == 'X') &&
            (objectiveFunction[i + 1] >= '0' && objectiveFunction[i + 1] <= '9'))
            objectiveFunction[i + 1] = ' ';
    }

    for (int i = 0; i < objectiveFunction.length(); i++)
        if (objectiveFunction[i] != ' ')
            temp = temp + objectiveFunction[i];

    return temp;
}

int countVariables(string str)
{
    int counter = 0;

    for (int i = 0; i < str.length(); i++)
        if (str[i] == 'x' || str[i] == 'X')
            counter++;
    return counter;
}

void updateCoefficientOfObjectiveFunction(string objectiveFunction, double equation[], int length)
 {
    for (int i = 0; i < length; i++)
        equation[i] = 0.0;

    int counter = 0;
    string temp = "";

    for (int i = 0; i < objectiveFunction.length(); i++)
    {
        if ((objectiveFunction[i] >= '0' && objectiveFunction[i] <= '9') || objectiveFunction[i] == '-' ||
            objectiveFunction[i] == '+')
            temp = temp + objectiveFunction[i];

        else if (objectiveFunction[i] == 'x' || objectiveFunction[i] == 'X')
        {
            istringstream iss(temp);
            if(temp=="")equation[counter]=1;
            iss >> equation[counter];
            counter++;
            temp = "";
        }
    }

}

void updateCoefficientOfConstrains(string constrain, double equation[], int length)
 {
    for (int i = 0; i < length; i++)
        equation[i] = 0;

    int counter = 0;
    string temp = "";

    for (int i = 0; i < constrain.length() + 1; i++)
    {
        if (i == constrain.length())
        {
            istringstream iss(temp);
            iss >> equation[counter];
            counter++;
            temp = "";
            break;
        } else if ((constrain[i] >= '0' && constrain[i] <= '9') || constrain[i] == '-' || constrain[i] == '+')
            temp = temp + constrain[i];

        else if (constrain[i] == 'x' || constrain[i] == 'X')
        {
            istringstream iss(temp);
            if(temp==""||temp=="+")equation[counter]=1;
            else if(temp=="-")equation[counter]=-1;
            else iss >> equation[counter];
            counter++;
            temp = "";
        }
    }

    for (int i = 0; i < length; i++)
    {
        if (equation[i] == 0)
        {
            double temp = equation[i - 1];
            equation[i - 1] = equation[length - 1];
            equation[length - 1] = temp;

            break;
        }
    }

}

void makeObjectiveFuntiontoMax(double function[], int length)
{
    for (int i = 0; i < length; i++)
        function[i] = function[i] * (-1);
}

void standardize(string constrain, double coeff[], int length, int numberOfConstrain,int constrainNumber)
{

    if (coeff[length - 1] < 0)
    {
        for (int i = 0; i < length; i++)
            coeff[i] = coeff[i] * (-1);

        int indexOfInequality = constrain.find("<=");

        if (indexOfInequality != -1)
            constrain[indexOfInequality] = '>';
        else {
            indexOfInequality = constrain.find(">=");
            constrain[indexOfInequality] = '<';
        }

    }

    int lessEqual = constrain.find("<=");

    if (lessEqual != -1)
        coeff[(length - 2) - (numberOfConstrain - 1) + constrainNumber] = 1;
    else
        coeff[(length - 2) - (numberOfConstrain - 1) + constrainNumber] = -1;
}

int search(double arr[], double key, int length)
 {
    for (int i = 0; i < length; i++) {
        //if(abs(arr[i]-key)<=0.0000001)
        if (arr[i] == key)
            return i;
    }
}

int getMaximum(double arr[], int startIndex, int endingIndex)
{
    int maxValue = INT_MIN;
    int maxIndex;

    for (int i = startIndex; i < endingIndex; i++) {
        if (arr[i] > maxValue)
            maxValue = arr[i], maxIndex = i;
    }

    return maxIndex;
}

bool isOptimized(double arr[], int startIndex, int endingIndex)
 {
    for (int i = startIndex; i < endingIndex; i++)
        if (arr[i] > 0)
            return false;

    return true;
}

string addCoefficient(string str)
{

    for (int i = 1; i < str.length(); i++)
    {
        if ((str[i] == 'x' || str[i] == 'X') && str[i - 1] == '0' && i == 1)
            str[i - 1] = '1';

        else if ((str[i] == 'x' || str[i] == 'X') && str[i - 1] == '0' && !(str[i - 2] >= '0' && str[i - 2] <= '9'))
            str[i - 1] = '1';
    }

    return str;
}

int main()
{

    int numberOfConstrain;
    string objectiveFunction;


    cout << "Enter the objective function:" << endl;
    getline(cin, objectiveFunction);
    objectiveFunction = addCoefficient(objectiveFunction);
    objectiveFunction = formatEquation(objectiveFunction);

    //cout << objectiveFunction << endl;

    cout << "Enter the number of constrains:" << endl;

    cin >> numberOfConstrain;

    string constrain[numberOfConstrain];

    string faltu;
    getline(cin,faltu);

    cout << "Enter the constrains:" << endl;

    for (int i = 0; i < numberOfConstrain; i++)
    {
        getline(cin, constrain[i]);
        constrain[i] = addCoefficient(constrain[i]);
        constrain[i] = formatEquation(constrain[i]);
        //cout << constrain[i] << endl;
    }

    int numberOfVariables = countVariables(objectiveFunction);

    int lengthOfcoefficientOfObjectiveFunction = numberOfConstrain + numberOfVariables;
    double coefficientOfObjectiveFunction[lengthOfcoefficientOfObjectiveFunction];
    double coefficientOfConstrains[numberOfConstrain][lengthOfcoefficientOfObjectiveFunction + 1];

    updateCoefficientOfObjectiveFunction(objectiveFunction, coefficientOfObjectiveFunction,
                                         lengthOfcoefficientOfObjectiveFunction);

    for (int i = 0; i < numberOfConstrain; i++)
        updateCoefficientOfConstrains(constrain[i], coefficientOfConstrains[i],
                                      lengthOfcoefficientOfObjectiveFunction + 1);


    cout << endl << "Is the problem minimization or maximization?\n1.Minimization\n2.Maximization\n";

    int choice;
    cin >> choice;

    cout << endl;

    if (choice == 1)
        makeObjectiveFuntiontoMax(coefficientOfObjectiveFunction, lengthOfcoefficientOfObjectiveFunction);

    for (int i = 0; i < numberOfConstrain; i++)
        standardize(constrain[i], coefficientOfConstrains[i],
                                       lengthOfcoefficientOfObjectiveFunction + 1, numberOfConstrain, i);

    int m = numberOfConstrain + 3;
    int n = lengthOfcoefficientOfObjectiveFunction + 3;
    double table[m][n];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            table[i][j] = INT_MAX;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //Objective function coeff except basic variable column(c_j)
            if (i == 0 && j > 0 && j < (n - 2))
                table[i][j] = coefficientOfObjectiveFunction[j - 1];

            //Value of basic variables
            if (j == 0 && i > 0 && i < m - 2)
                table[i][j] = 0;

            //Coefficients of constrains
            if (i > 0 && j > 0 && i < m - 2 && j < n - 1)
                table[i][j] = coefficientOfConstrains[i - 1][j - 1];

            //Initializing z_j = sum of ((basic variable value)*constrain coefficient)
            if (i == (m - 2) && j > 0 && j < (n - 2))
                table[i][j] = 0;
            //(c_j-z_j)
            if (i == (m - 1) && j > 0 && j < (n - 2))
                table[i][j] = table[0][j] - table[i - 1][j];
        }
    }


    cout << endl;

    while (true)
    {
        int pivotColumn = getMaximum(table[m - 1], 1, n - 2);

        for (int i = 1; i < m - 2; i++)
        {
            if (table[i][pivotColumn] > 0)
                table[i][n - 1] = table[i][n - 2] / table[i][pivotColumn];
            else
                table[i][n - 1] = INT_MAX;
        }

        int pivotRow;

        int minValue = INT_MAX;
        int minIndex;

        for (int i = 1; i < m - 2; i++) {
            if (table[i][n - 1] < minValue)
                minValue = table[i][n - 1], minIndex = i;
        }

        pivotRow = minIndex;

        table[pivotRow][0] = table[0][pivotColumn];

        for (int i = 1; i < m - 2; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                if (i != pivotRow && j != pivotColumn)
                 {
                    double oldValue = table[i][j];
                    table[i][j] = oldValue - ((table[pivotRow][j] * table[i][pivotColumn]) /table[pivotRow][pivotColumn]);
                }
            }

            if (i != pivotRow)
                table[i][pivotColumn] = 0;
        }

        double pivot = table[pivotRow][pivotColumn];
        for (int i = 1; i < n - 1; i++)
            table[pivotRow][i] = table[pivotRow][i] / pivot;

        for (int j = 1; j < n - 2; j++) {
            double sum = 0;
            for (int i = 1; i < m - 2; i++) {
                sum = sum + table[i][0] * table[i][j];
            }

            table[m - 2][j] = sum;
        }

        for (int i = 1; i < n - 2; i++)
            table[m - 1][i] = table[0][i] - table[m - 2][i];


        cout << "pivot: " << pivot << endl;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                cout << table[i][j] << "\t";

            cout << endl;
        }
        cout << endl;

        if(isOptimized(table[m - 1], 1, n - 2)) break;

    }

    double solution = 0;

    for (int i = 1; i < m - 2; i++)
        solution = solution + table[i][0] * table[i][n - 2];

    cout << "Solution is: " << solution << endl;

    for (int i = 1; i < m - 2; i++)
    {
        if (table[i][0] > 0)
        {
            int index = search(coefficientOfObjectiveFunction, table[i][0], lengthOfcoefficientOfObjectiveFunction);
            //if (coefficientOfConstrains[index] != 0)
            cout << "x" << index + 1 << " : " << table[i][n - 2] << endl;
        }
    }

    return 0;
}
