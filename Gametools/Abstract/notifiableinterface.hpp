#ifndef NOTIFIABLEINTERFACE_HPP
#define NOTIFIABLEINTERFACE_HPP

class NotifiableInterface{
public:
    NotifiableInterface() = default;
    virtual ~NotifiableInterface() = default;

    virtual void notify(unsigned int code) = 0;
};

#endif // NOTIFIABLEINTERFACE_HPP
