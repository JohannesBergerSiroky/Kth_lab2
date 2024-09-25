/* Lab 2. KTH Elektroteknik. The debug functions remain intact. */

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



/*********** Function declarations for the program. *********************************************/

int measurementHandler(char mCommand, int msrData[], int cmpData[], int enteredSize);
void viewMeasureData(int vData[], int vSize);
int enterMeasurementData(int eData[], int eSize);
void computeMeasurementData(int givenData[], int computeData[], int cSize);
int resetMeasurementData(int rData[], int rcData[], int rSize);
float averageValue(int aData[], int aSize);
float printnormalValue(int nData[], int compData[], int nSize);
int maxValue(int maxData[], int maxSize);
int minValue(int minData[], int minSize);

/************ End function declarations ***********************************************************/





/*************************************** Function definitions ***************************************/



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

/* Resets both Arrays to zero. */
int resetMeasurementData(int rData[], int rcData[], int rSize)
{
        for(int i = 0; i < rSize;i++) {
                rData[i] = 0;
                rcData[i] = 0;
        }
        return 0;
}

/* Gets the average value from the measurent array. */
float averageValue(int aData[], int aSize)
{

        float avgValue = 0;
        /* The size cannot be zero. */
        if(aSize > 0) {

                int sum = 0;
                for (int i = 0; i < aSize; i++) {
                        sum = sum + aData[i];
                }
                avgValue = ((float)sum / (float)aSize);
        }

        return avgValue;
}

/* Prints the normal value from an array which got the original data 
 * from another array. 
*/
void printNormalValue(int nData[], int compData[], int nSize)
{
        int average = averageValue(nData, nSize);
        printf("\n[");
        for (int i = 0; i < nSize; i++) {
                compData[i] = nData[i] - average;
                printf("%d ", compData[i]);
        }
        printf("]\n");

}

/* Returns the max value from an array. */
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
/* Returns the min value from an array. */
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
/* It is the view function which prints data from the array. 
 * It prints the measurement data from user input. 
*/
void viewMeasureData(int vData[], int vSize)
{
        printf("[");
        for (int i = 0; i < vSize; i++) {
                printf("%d ", vData[i]);
        }
        printf("]\n");
}

/* It is a function which gets modified data from other function and 
 * presents them here.
 */
void computeMeasurementData(int givenData[], int computeData[], int cSize)
{
        printf("\nMax Value: %d\n", maxData(givenData, cSize)); 
        printf("\nMin Value: %d\n", minData(givenData, cSize)); 
        printf("\nAverage Value: %.2f\n", averageValue(givenData, cSize)); 
        printf("\nNormal Value: "); 
        printNormalValue(givenData, computeData, cSize); 
}

/* This is the first function except form main that is entered. 
 * It passes the value entered from a user in the main function
 * to other functions.
*/
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

/************************************** End function definitions ****************************************/


/************************************** Main function ***************************************************/
int main(int argc, char **argv) 
{
        int measurementArray[MAX_SIZE] = {};
        int computingPlaceholder[MAX_SIZE] = {};
        int currentSize = 0;
        int streamCheck = 0;

        char cmd = '0';
	    //commented code: dbgEnter("main");
	    //commented code: dbgInspect("main", "dbg level", DBGLEVEL);

	    printf("Starting Lab #2. v = view, e = enter values or enter a value\n");
        printf("c = Compute. r = reset all measurements. q = quit.\n");
	    
        do {
                //commented code; if(cmd) {
	                    printf("\nVECRQ: ");
                //commented code: }

                scanf("%c", &cmd);
                //commented code: if (cmd && (cmd != '\n') && (cmd != ' ')) {

                        /* User input will be processed in measurementHandler. */
                        currentSize = measurementHandler(cmd, measurementArray, computingPlaceholder, currentSize);

                //commented code: }
                /*commented code: if (cmd == '\n') {
                        cmd = '\0';
                }*/

                /* The stdin can be cleared with the getchar() function. */
                while((streamCheck = getchar()) != '\n' && (streamCheck != EOF));

        } while ((cmd != 'q'));
	    
	    printf("...Lab #2 done, bye!\n");
        //commented code: dbgExit("Exiting main.");
	    return 0;
}
