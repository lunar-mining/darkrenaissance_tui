#include <cdk.h>

int main (int argc, char **argv)
{
    CDKSCREEN *cdkscreen;
    CDKDIALOG *question;
    const char *buttons[6];
    const char *message[1];
    const char *info[2];
    //char *loginName = 0;
    char temp[256];
    int selection;
    CDK_PARAMS params;

    CDKparseParams (argc, argv, &params, CDK_MIN_PARAMS);

    cdkscreen = initCDKScreen (NULL);

    // start color
    initCDKColor();

    // set up the dialog box
    message[0] = "<C></56>DARK RENAISSANCE WALLET";
    buttons[0] = "</56>send";
    buttons[1] = "</56>receive";
    buttons[2] = "</56>balance";
    buttons[3] = "</56>history";
    buttons[4] = "</56>export";
    buttons[5] = "</56>quit";

    // Create the dialog box

    question = newCDKDialog (cdkscreen,
                CDKparamValue (&params, 'X', CENTER),
                CDKparamValue (&params, 'Y', CENTER),
                (CDK_CSTRING2) message, 1,
                (CDK_CSTRING2) buttons, 6,
                A_REVERSE,
                TRUE,
                CDKparamValue (&params, 'N', TRUE),
                CDKparamValue (&params, 'S', FALSE));

    // check if it is null value
    if (question == (CDKDIALOG *)0)
    {
        destroyCDKScreen (cdkscreen);
        // end curses
        endCDK ();

        printf("Cannot create dialog box.\n");
    }
    
    // create key binding
    bindCDKObject (vDIALOG, question, '?', dialogHelpCB, 0);

    // activate dialog box
    selection = 0;
    // while (selection = getch() !=5)
    while (selection != 5)
    {   
        // get the users button selection
        selection = activateCDKDialog (question, (chtype *)0);
        switch(selection)                                                 
        {

            case 0:
            {
                info[0] = "<C></56>Send bitcoin";
                // send function
                popupLabel (ScreenOf (question), (CDK_CSTRING2) info, 2);
                break;
            }
            case 1:
            {
                info[0] = "<C></56>Receive bitcoin";
                info[1] = temp;
                popupLabel (ScreenOf (question), (CDK_CSTRING2) info, 2);
                // receive 
                break;
            }
            case 2:
            {
                info[0] = "<C></56>Balance";
                info[1] = temp;
                popupLabel (ScreenOf (question), (CDK_CSTRING2) info, 2);  
                // do balance
                break;
            }
            case 3:
            {   
                info[0] = "<C></56>History";
                info[1] = temp;
                popupLabel (ScreenOf (question), (CDK_CSTRING2) info, 2);  
                // do history
                break;
            }
            case 4:
            {
                info[0] = "<C></56>Export keys";
                info[1] = temp;
                popupLabel (ScreenOf (question), (CDK_CSTRING2) info, 2);
                // export
                break;
            }
        }
    }

    // clean up
    destroyCDKDialog (question);
    destroyCDKScreen (cdkscreen);
    endCDK ();
}

