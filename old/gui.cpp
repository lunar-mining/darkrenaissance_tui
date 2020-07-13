#include <cdk.h>

static int dialogHelpCB (EObjectType cdktype GCC_UNUSED,
                        void *object,
                        void *clientData GCC_UNUSED,
                        chtype key GCC_UNUSED)
{
    CDKDIALOG *dialog = (CDKDIALOG *)object;
    const char *mesg;
    int choice;

    while (choice = getch())
    {
        switch(choice)
        {
            case 0:
            {
                mesg = "send";
                popupLabel (ScreenOf (dialog), (CDK_CSTRING2) mesg, 1);
                break;
            }
            case 1:
            {
                mesg = "receive";
                popupLabel (ScreenOf (dialog), (CDK_CSTRING2) mesg, 1);
                break;
            }
            case 2:
            {
                mesg = "balance";
                popupLabel (ScreenOf (dialog), (CDK_CSTRING2) mesg, 1);
                break;
            } 
            case 3:
            {
                mesg = "history";
                popupLabel (ScreenOf (dialog), (CDK_CSTRING2) mesg, 1);
                break;
            }
            case 4:
            {
                mesg = "export";
                popupLabel (ScreenOf (dialog), (CDK_CSTRING2) mesg, 1);
                break;
            }
            default:                                                     
            {
                return false;
            }
        }
    }
    return 0;
}
