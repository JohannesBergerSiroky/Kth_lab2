/* Lab 2. KTH Elektroteknik. */

#include <stdio.h>
#define DBGLEVEL 2
#define MAX_SIZE 10

                      // 2..0 Most verbose to none

//*** Debug package ***********************************************
void dbgEnter(char *msg) 
{
	    switch (DBGLEVEL) {
		    case 2: printf(">>> %s\n",msg); //break intensional omitted
	    }
}
void dbgExit(char *msg) 
{
	    switch (DBGLEVEL) {
		    case 2: printf("<<< %s\n",msg); //break intensional omitted
	    }
}
void dbgInspect(char *msg, char *id, int value) 
{
	    switch (DBGLEVEL) {
		    case 1:                         //break intensional omitted
		    case 2: printf("--- %s: %s=%d\n",
		                   msg, id, value); //break intensional omitted
	    }
}
//*** DBGP END ***************************************************

//*** Other packages *********************************************



int measurementHandler(char mCommand, int msrData[], int cmpData[], int enteredSize);
void viewMeasureData(int vData[], int vSize);
int enterMeasurementData(int eData[], int eSize);
void computeMeasurementData(int givenData[], int computeData[], int cSize);
int resetMeasurementData(int rData[], int rcData[], int rSize);
float averageValue(int aData[], int aSize);
float normalValue(int nData[], int nSize);
int maxValue(int maxData[], int maxSize);
int minValue(int minData[], int minSize);



/* This is code for entering data. A zero cannot be entered.
 * Instead a zero will make the input process end.
 */
int enterMeasurementData(int eData[], int eSize)
{
        int command = 0;
        do {
                printf("\nEnter a measurement (0 to quit): ");
                scanf("%d", &command);

                if((command != 0)  && (eSize < MAX_SIZE)) {
                        eData[eSize] = command;
                        eSize++;
                }

        } while ((command != 0) && (eSize < MAX_SIZE));

        if (eSize >= MAX_SIZE) {
                printf("\nToo many measurement variables.\n");
        }

        return eSize;
}

int resetMeasurementData(int rData[], int rcData[], int rSize)
{
        for(int i = 0; i < rSize;i++) {
                rData[i] = 0;
                rcData[i] = 0;
        }
        return 0;
}

float averageValue(int aData[], int aSize)
{

        float avgValue = 0;
        if(aSize > 0) {

                int sum = 0;
                for (int i = 0; i < aSize; i++) {
                        sum = sum + aData[i];
                }
                avgValue = (float)(sum / aSize);
        }

        return avgValue;
}

void getNormalValue(int nData[], int compData[], int nSize)
{
        int average = averageValue(nData, nSize);
        printf("\n[");
        for (int i = 0; i < nSize; i++) {
                compData[i] = nData[i] - average;
                printf("%d ", compData[i]);
        }
        printf("]\n");

}

int maxData(int maxData[], int maxSize)
{
        int currentMaxValue = maxData[0];
        for(int i = 0; i < (maxSize - 1); i++) {
                if(maxData[i+1] > maxData[i]) {
                        currentMaxValue = maxData[i+1];
                }
        }
        return currentMaxValue;
}

int minData(int minData[], int minSize)
{
        int currentMinValue = minData[0];
        for(int i = 0; i < (minSize - 1); i++) {
                if(minData[i+1] < minData[i]) {
                        currentMinValue = minData[i + 1];
                }
        }
        return currentMinValue;
}

void viewMeasureData(int vData[], int vSize)
{
        printf("[");
        for (int i = 0; i < vSize; i++) {
                printf("%d ", vData[i]);
        }
        printf("]\n");
}

void computeMeasurementData(int givenData[], int computeData[], int cSize)
{
        printf("\nMax Value: %d\n", maxData(givenData, cSize)); 
        printf("\nMin Value: %d\n", minData(givenData, cSize)); 
        printf("\nAverage Value: %.2f\n", averageValue(givenData, cSize)); 
        printf("\nNormal Value: "); 
        getNormalValue(givenData, computeData, cSize); 
}

int measurementHandler(char mCommand, int Data[], int cData[], int enteredSize)
{
        switch (mCommand) {
                case 'q': 
                        break;
                case 'v':
                        viewMeasureData(Data, enteredSize);
                        break;
                case 'e':
                        enteredSize = enterMeasurementData(Data, enteredSize);
                        break;
                case 'c':
                        computeMeasurementData(Data, cData, enteredSize);
                        break;
                case 'r': 
                        enteredSize = resetMeasurementData(Data, cData, enteredSize);
                        break;
                default: 
                        printf("\nUsage: Type v, e, c, r or q\n");
        }
        return enteredSize;

}

int main(int argc, char **argv) 
{
        int measurementArray[MAX_SIZE] = {};
        int computingPlaceholder[MAX_SIZE] = {};
        int currentSize = 0;
        int streamCheck = 0;

        char cmd = '0';
	    dbgEnter("main");
	    dbgInspect("main", "dbg level", DBGLEVEL);
	    printf("Starting Lab #2. v = view, e = enter values or enter a value\n");
        printf("c = Compute. r = reset all measurements. q = quit.\n");
	    
        do {
                //if(cmd) {
	                    printf("\nVECRQ: ");
                //}

                scanf("%c", &cmd);
                if (cmd && (cmd != '\n') && (cmd != ' ')) {
                        currentSize = measurementHandler(cmd, measurementArray, computingPlaceholder, currentSize);

                }
                /*if (cmd == '\n') {
                        cmd = '\0';
                }*/
                while((streamCheck = getchar()) != '\n' && (streamCheck != EOF));

        } while ((cmd != 'q'));
	    
	    printf("...Lab #2 done, bye!\n");
        dbgExit("Exiting main.");
	    return 0;
}
