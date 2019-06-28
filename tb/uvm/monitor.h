#ifndef VIP_MONITOR_H_
#define VIP_MONITOR_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "vip_if.h"

#include <stdlib.h>

class monitor : public uvm::uvm_monitor
{
  protected:
  vip_if* dut_vif ;

  std::string name_vif;
  public:      
      
  monitor(uvm::uvm_component_name name)
  : uvm_monitor(name)
  {
      name_vif = name;
  }
  UVM_COMPONENT_UTILS(monitor);

  void build_phase(uvm::uvm_phase& phase)
  {
    uvm::uvm_monitor::build_phase(phase);
    dut_vif = new vip_if();
    uvm::uvm_config_db<vip_if*>::get(0, "", name_vif, dut_vif);
  }

  void run_phase(uvm::uvm_phase& phase)
  {
    phase.raise_objection(this);    
    UVM_INFO("", "TEST START", uvm::UVM_MEDIUM);    
    dut_vif -> nrst = 0;
    wait(10, SC_NS);
    dut_vif -> nrst = 1;
    
    wait(100, SC_MS);
    UVM_INFO("", "TEST FINISH", uvm::UVM_MEDIUM);
    phase.drop_objection(this);
  }      



};

#endif 
