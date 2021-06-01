
/* #include "nil/NilRTOS.h"
#include "nil/NilRTOS.c"
#include "nil/board.c"
#include "nil/nilcore.c"
#include "nil/nilUtility.cpp"
#include "nil/nil.c"
*/
// #include <NilRTOS.h>
#include <ChNil.h>

SEMAPHORE_DECL(lockTimeCriticalZone, 1); // only one process in some specific zones

#include <avr/wdt.h> // watchdog for automatic reboot in case of crash

//#include "time/Time.cpp" // git clone https://github.com/PaulStoffregen/Time
#include <Time.h>

/*#include "hack/NullStream.h"
#include "hack/toHex.h"
#include "hack/Utility.h"
#include "hack/params.h"
#include "hack/eeprom.h"
#include "hack/eepromLogger.h"
#include "hack/sstLogger.h"
#include "hack/WireSlave.h"
#include "hack/WireMaster.h"
#include "hack/SerialUtilities.h"
#include "hack/Serial.h"
#include "hack/status.h"
#include "hack/start.h"
*/

//#include <NullStream.h>
#include <toHex.h>
#include <WireMaster.h>

