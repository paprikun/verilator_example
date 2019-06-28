#ifndef VIP_IF_H_
#define VIP_IF_H_

#include <systemc>
#include <uvm>

class vip_if
{
    public:
    sc_signal<bool>            nrst;
    sc_signal<bool>            pwm;
    vip_if() {}

};
#endif
