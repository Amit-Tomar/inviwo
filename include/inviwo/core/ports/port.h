#ifndef IVW_PORT_H
#define IVW_PORT_H

#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/common/inviwocoredefine.h>

namespace inviwo {

class Processor;

class IVW_CORE_API Port {

friend class Processor;

public:
    enum PortDirection {
        OUTPORT = 0,
        INPORT = 1
    };

    /**
     * Constructor for creating port instances. As this class is abstract, the constructor is not
     * called directly. Instead, constructors of the derived classes call this constructor.
     *
     * @param direction Defines if this is an INPORT or an OUTPORT.
     * @param identifier Port identifier used for serialization. Should be unique within the scope
                         of a processor.
     * @see Processor::addPort()
     */
    Port(PortDirection direction, std::string identifier);
    virtual ~Port();

    /**
     * Initializes the port. Here we can for instance initialize data to be stored inside the port.
     * As this method is pure virtual, it needs to be implemented within derived classes that should
     * be instantiated.
     * @see deinitialize()
     */
    virtual void initialize() = 0;

    /**
     * Deinitializes the port by reverting the initialization performed in initialize().
     * As this method is pure virtual, it needs to be implemented within derived classes that should
     * be instantiated.
     * @see initialize()
     */
    virtual void deinitialize() = 0;

    /**
     * Returns the RGB color code used to colorize all ports of this type. This color code is for
     * instance used in the NetworkEditor. To distinguish different port types through their color,
     * this method should be overloaded in derived classes.
     */
    virtual uvec3 getColorCode() const { return uvec3(128,128,128); }


    virtual void connectTo(Port* port);
    virtual void disconnectFrom(Port* port);

    Processor* getProcessor() const { return processor_; }
    std::string getIdentifier() const {return identifier_; }

    bool isOutport() const { return (direction_ == Port::OUTPORT); }
    bool isInport() const { return (direction_ == Port::INPORT); }
    bool isConnected() const { return !(connectedPorts_.empty()); }
    bool isConnectedTo(Port* port) const {
        return !(std::find(connectedPorts_.begin(),connectedPorts_.end(),port)==connectedPorts_.end());
    }

    void invalidate();

protected:
    PortDirection direction_;
    std::string identifier_;

    void setIdentifier(const std::string& name);
    void setProcessor(Processor* processor) { processor_ = processor; }

private:
    Processor* processor_;
    std::vector<Port*> connectedPorts_;
};


class IVW_CORE_API Port2 {

friend class Processor;

public:
    Port2(std::string identifier);
    virtual ~Port2();

    virtual void initialize() = 0;
    virtual void deinitialize() = 0;

    virtual uvec3 getColorCode() const { return uvec3(128,128,128); }

    Processor* getProcessor() const { return processor_; }
    std::string getIdentifier() const {return identifier_; }

    virtual bool isOutport() const = 0;
    virtual bool isInport() const = 0;
    virtual bool isConnected() const = 0;

    virtual void invalidate() = 0;

protected:
    std::string identifier_;

    void setIdentifier(const std::string& name);
    void setProcessor(Processor* processor) { processor_ = processor; }

private:
    Processor* processor_;
};

} // namespace

#endif // IVW_PORT_H
