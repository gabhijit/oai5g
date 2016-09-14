#include <stdio.h>
#include "time_meas.h"
#include <math.h>
#include <unistd.h>

// global var for openair performance profiler
int opp_enabled = 0;


double get_cpu_freq_GHz(void) {

  time_stats_t ts = {0};
  reset_meas(&ts);
  ts.trials++;
  ts.in = rdtsc_oai();
  sleep(1);
  ts.diff = (rdtsc_oai()-ts.in);
  cpu_freq_GHz = (double)ts.diff/1000000000;
  printf("CPU Freq is %f \n", cpu_freq_GHz);
  return cpu_freq_GHz; 
}

void print_meas_now(time_stats_t *ts, const char* name, int subframe, FILE* file_name){

  if (opp_enabled) {

    //static double cpu_freq_GHz = 3.2;

    //if (cpu_freq_GHz == 0.0)
      //cpu_freq_GHz = get_cpu_freq_GHz(); // super slow

    if (ts->trials>0) {

      //fprintf(file_name,"Name %25s: Processing %15.3f ms for SF %d, diff_now %15.3f \n", name,(ts->diff_now/(cpu_freq_GHz*1000000.0)),subframe,ts->diff_now);
      fprintf(file_name,"%15.3f ms, diff_now %15.3f \n",(ts->diff_now/(cpu_freq_GHz*1000000.0)),(double)ts->diff_now);
      
    }
  }
}

void print_meas(time_stats_t *ts, const char* name, time_stats_t * total_exec_time, time_stats_t * sf_exec_time)
{

  if (opp_enabled) {

    static int first_time = 0;
    static double cpu_freq_GHz = 0.0;

    if (cpu_freq_GHz == 0.0)
      cpu_freq_GHz = get_cpu_freq_GHz();

    if (first_time == 0) {
      first_time=1;

      if ((total_exec_time == NULL) || (sf_exec_time== NULL))
        fprintf(stderr, "%25s  %25s  %25s  %25s %25s %6f\n","Name","Total","Per Trials",   "Num Trials","CPU_F_GHz", cpu_freq_GHz);
      else
        fprintf(stderr, "%25s  %25s  %25s  %20s %15s %6f\n","Name","Total","Average/Frame","Trials",    "CPU_F_GHz", cpu_freq_GHz);
    }

    if (ts->trials>0) {
      //printf("%20s: total: %10.3f ms, average: %10.3f us (%10d trials)\n", name, ts->diff/cpu_freq_GHz/1000000.0, ts->diff/ts->trials/cpu_freq_GHz/1000.0, ts->trials);

      if ((total_exec_time == NULL) || (sf_exec_time== NULL)) {
        fprintf(stderr, "%25s:  %15.3f ms ;  %15.3f us; %15d;\n",
                name,
                (ts->diff/cpu_freq_GHz/1000000.0),
                (ts->diff/ts->trials/cpu_freq_GHz/1000.0),
                ts->trials);
      } else {
        fprintf(stderr, "%25s:  %15.3f ms (%5.2f%%); %15.3f us (%5.2f%%); %15d;\n",
                name,
                (ts->diff/cpu_freq_GHz/1000000.0),
                ((ts->diff/cpu_freq_GHz/1000000.0)/(total_exec_time->diff/cpu_freq_GHz/1000000.0))*100,  // percentage
                (ts->diff/ts->trials/cpu_freq_GHz/1000.0),
                ((ts->diff/ts->trials/cpu_freq_GHz/1000.0)/(sf_exec_time->diff/sf_exec_time->trials/cpu_freq_GHz/1000.0))*100,  // percentage
                ts->trials);
      }
    }
  }

}

double get_time_meas_us(time_stats_t *ts)
{

  static double cpu_freq_GHz = 0.0;

  if (cpu_freq_GHz == 0.0)
    cpu_freq_GHz = get_cpu_freq_GHz();

  if (ts->trials>0)
    return  (ts->diff/ts->trials/cpu_freq_GHz/1000.0);

  return 0;
}
