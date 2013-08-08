#ifndef CSP_H
#define CSP_H

#include <vector>
#include <stdio.h>

using namespace std;

struct binary_constraint_t {
  int id;
  int var1;
  int var2;
};

struct assignment_t {
  int variable;
  int value;
};

struct interval_t {
  int l;
  int h;
};

struct interval_node_t {
  interval_t interval;
  interval_node_t* next;
};

class domain_t {
  private:
    vector<interval_t> backup_intervals;
  public:
    int variable;
    vector<interval_t> intervals;

    void print() {
      vector<interval_t>::iterator interval;
      for (interval = intervals.begin(); interval != intervals.end(); interval++) {
        printf("[%d, %d]", interval->l, interval->h);
      }
      printf("\n");
    }

    assignment_t select_assignment() {
      assignment_t assignment;
      if (is_empty()) { return assignment; }
      assignment.variable = variable;
      assignment.value    = intervals[0].l;
      return assignment;
    }

    void perform_assignment(assignment_t assignment) {
      backup_intervals = intervals;
      intervals.clear();
      interval_t interval;
      interval.l = assignment.value;
      interval.h = assignment.value;
      intervals.push_back(interval);
    }

    void revert_assignment(assignment_t assignment) {
      intervals = backup_intervals;
      intervals[0].l++;
    }

    void split(int interval, int value) {
      if (value == intervals[interval].l) {
        intervals[interval].l++;
        if (intervals[interval].l > intervals[interval].h) intervals.erase(intervals.begin()+interval);
        return;
      } else if (value == intervals[interval].h) {
        intervals[interval].h--;
        if (intervals[interval].l > intervals[interval].h) intervals.erase(intervals.begin()+interval);
        return;
      }
      interval_t new_interval;
      new_interval.l = value+1;
      new_interval.h = intervals[interval].h;
      intervals[interval].h = value-1;
      intervals.insert(intervals.begin()+interval, new_interval);
    }

    bool is_empty() {
      vector<interval_t>::iterator i;
      for(i=intervals.begin(); i!=intervals.end(); i++) {
        if (i->h >= i->l) {
          return false;
        }
      }
      return true;
    }    

    domain_t deep_copy() {
      domain_t domain;
      domain.variable = variable;
      vector<interval_t>::iterator i;
      for(i=intervals.begin(); i!=intervals.end(); i++) {
        interval_t interval;
        interval.l = i->l;
        interval.h = i->h;
        domain.intervals.push_back(interval);
      }
      return domain;
    }

    void restore(const domain_t& backup_vector) {
      intervals.clear();
      vector<interval_t>::const_iterator i;
      for(i=backup_vector.intervals.begin(); i!=backup_vector.intervals.end(); i++) {
        interval_t interval;
        interval.l = i->l;
        interval.h = i->h;
        intervals.push_back(interval);        
      }
    }

};

class csp_t {
  public:
    int* coefs;
    int* cterms;
    domain_t* domains;
    int vnum;
    int cnum;

    csp_t(int* mcoefs, int* mcterms, domain_t* mdomains, int mvnum, int mcnum) :
      coefs(mcoefs), cterms(mcterms), domains(mdomains), vnum(mvnum), cnum(mcnum) {

    }

};

#endif /*CSP_H*/
