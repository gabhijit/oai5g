/** @defgroup _intertask_interface_impl_ Intertask Interface Mechanisms
 * Implementation
 * @ingroup _ref_implementation_
 * @{
 */

/********************************************************************************
 *
 * !!! This header should only be included by the file that initialize
 *     the intertask interface module for the process !!!
 *
 * Other files should include "intertask_interface.h"
 *
 *******************************************************************************/

#ifndef INTERTASK_INTERFACE_INIT_H_
#define INTERTASK_INTERFACE_INIT_H_

#include "intertask_interface.h"

#ifndef CHECK_PROTOTYPE_ONLY

const char * const messages_definition_xml = {
#include "messages_xml.h"
};

/* Map task id to printable name. */
const task_info_t tasks_info[] = {
  {0, TASK_UNKNOWN, 0, 0, "TASK_UNKNOWN"},
#define TASK_DEF(tHREADiD, pRIO, qUEUEsIZE)          { tHREADiD##_THREAD, TASK_UNKNOWN, pRIO, qUEUEsIZE, #tHREADiD },
#define SUB_TASK_DEF(tHREADiD, sUBtASKiD, qUEUEsIZE) { sUBtASKiD##_THREAD, tHREADiD##_THREAD, 0, qUEUEsIZE, #sUBtASKiD },
#include <tasks_def.h>
#undef SUB_TASK_DEF
#undef TASK_DEF
};

/* Map message id to message information */
const message_info_t messages_info[] = {
#define MESSAGE_DEF(iD, pRIO, sTRUCT, fIELDnAME) { iD, pRIO, sizeof(sTRUCT), #iD },
#include <messages_def.h>
#undef MESSAGE_DEF
};

#endif

/** \brief Init function for the intertask interface. Init queues, Mutexes and Cond vars.
 * \param thread_max Maximum number of threads
 * \param messages_id_max Maximum message id
 * \param threads_name Pointer on the threads name information as created by this include file
 * \param messages_info Pointer on messages information as created by this include file
 **/
int itti_init(task_id_t task_max, thread_id_t thread_max, MessagesIds messages_id_max, const task_info_t *tasks_info,
              const message_info_t *messages_info, const char * const messages_definition_xml,
              const char * const dump_file_name);

#endif /* INTERTASK_INTERFACE_INIT_H_ */
/* @} */
