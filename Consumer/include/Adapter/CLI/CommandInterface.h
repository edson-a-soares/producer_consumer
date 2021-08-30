#ifndef Consumer_CLI_CommandInterface_INCLUDED
#define Consumer_CLI_CommandInterface_INCLUDED

namespace Consumer {
namespace CLI {


    class CommandInterface
    {
    public:
        virtual ~CommandInterface() = default;
        virtual void showHelp() = 0;
        virtual void showArgumentsHelp() = 0;
        virtual int execute(int, char * []) = 0;

    };


} }

#endif
