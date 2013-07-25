#ifndef _INCL_STEAMSHIM_CHILD_H_
#define _INCL_STEAMSHIM_CHILD_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum STEAMSHIM_EventType
{
    SHIMEVENT_BYE,
    SHIMEVENT_PUMPED,
    SHIMEVENT_STATSRECEIVED,
    SHIMEVENT_STATSSTORED,
    SHIMEVENT_SETACHIEVEMENT,
    SHIMEVENT_GETACHIEVEMENT,
    SHIMEVENT_RESETSTATS,
    SHIMEVENT_SETSTATI,
    SHIMEVENT_GETSTATI,
    SHIMEVENT_SETSTATF,
    SHIMEVENT_GETSTATF,
} STEAMSHIM_EventType;

/* not all of these fields make sense in a given event. */
typedef struct STEAMSHIM_Event
{
    STEAMSHIM_EventType type;
    int okay;
    int ivalue;
    float fvalue;
    unsigned long long epochsecs;
    char name[256];
} STEAMSHIM_Event;

int STEAMSHIM_init(void);  /* non-zero on success, zero on failure. */
void STEAMSHIM_deinit(void);
int STEAMSHIM_alive(void);
const STEAMSHIM_Event *STEAMSHIM_pump(void);

#ifdef __cplusplus
}
#endif

#endif  /* include-once blocker */

/* end of steamshim_child.h ... */

