#include "steamshim_child.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static void printEvent(const STEAMSHIM_Event *e)
{
    if (!e) return;

    printf("CHILD EVENT: ");
    switch (e->type)
    {
        #define PRINTGOTEVENT(x) case SHIMEVENT_##x: printf("%s(", #x); break
        PRINTGOTEVENT(BYE);
        PRINTGOTEVENT(PUMPED);
        PRINTGOTEVENT(STATSRECEIVED);
        PRINTGOTEVENT(STATSSTORED);
        PRINTGOTEVENT(SETACHIEVEMENT);
        PRINTGOTEVENT(GETACHIEVEMENT);
        PRINTGOTEVENT(RESETSTATS);
        PRINTGOTEVENT(SETSTATI);
        PRINTGOTEVENT(GETSTATI);
        PRINTGOTEVENT(SETSTATF);
        PRINTGOTEVENT(GETSTATF);
        #undef PRINTGOTEVENT
        default: printf("UNKNOWN("); break;
    } /* switch */

    printf("%sokay, ival=%d, fval=%f, time=%llu, name='%s').\n",
            e->okay ? "" : "!", e->ivalue, e->fvalue, e->epochsecs, e->name);
} /* printEvent */

int main(int argc, char **argv)
{
    const int retval = (int) time(NULL) % 127;
    int i;

    printf("Child argv (argc=%d):\n", argc);
    for (i = 0; i <= argc; i++)
        printf("  - '%s'\n", argv[i]);
    printf("\n");

    if (!STEAMSHIM_init())
    {
        printf("Child init failed, terminating.\n");
        return 42;
    } /* if */

    STEAMSHIM_requestStats();
    while (STEAMSHIM_alive())
    {
        const STEAMSHIM_Event *e = STEAMSHIM_pump();
        printEvent(e);
        if (e && e->type == SHIMEVENT_STATSRECEIVED)
            break;
        usleep(100 * 1000);
    } // while

    STEAMSHIM_getStatI("BulletsFired");
    STEAMSHIM_getAchievement("KILL_FIRST_VICTIM");

    STEAMSHIM_resetStats(1);
    STEAMSHIM_storeStats();

    STEAMSHIM_setAchievement("KILL_FIRST_VICTIM", 1);
    STEAMSHIM_getAchievement("KILL_FIRST_VICTIM");
    STEAMSHIM_setStatI("BulletsFired", 22);
    STEAMSHIM_storeStats();

    {
        time_t x = time(NULL) + 5;

        while ( STEAMSHIM_alive() && (time(NULL) < x) )
        {
            const STEAMSHIM_Event *e = STEAMSHIM_pump();
            printEvent(e);
            usleep(100 * 1000);
        } // while
    }

    STEAMSHIM_deinit();

    sleep(10);

    printf("Child returning %d\n", retval);
    return retval;
} /* main */

