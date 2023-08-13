#include <iostream>
#include <fstream>
#include <vector>
class Generator;
class Generator_State
{
public:
    virtual std::string getline(Generator *) = 0;
    ~Generator_State(){};
};
class NORMAL_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class ADD_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class COPY_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class ENV_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class FROM_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class HELP_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class IGNORE_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class CMD_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class ENTRY_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class EXPOSE_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class RUN_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class SKIP_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class ERROR_STATE : public Generator_State
{
    virtual std::string getline(Generator *) override;
};
class Generator
{
private:
    bool _eof;
    Generator_State *_state;
    int _index;
    std::vector<std::string> _tokens;
    std::string _output;

public:
    Generator(std::vector<std::string> tokens)
    {
        this->_eof = false;
        this->_state = new NORMAL_STATE();
        this->_index = 0;
        this->_tokens = tokens;
        this->_output = "";
    };
    ~Generator(){};
    std::string getToken()
    {
        if (this->_index > this->_tokens.size())
        {
            this->_eof = true;
            return "";
        }
        return this->_tokens[this->_index++];
    };
    std::string getline() { return _state->getline(this); };
    void setState(Generator_State *new_state)
    {
        delete this->_state;
        this->_state = new_state;
    };
    bool is_EOF() { return this->_eof; };
    std::string getOutput() { return this->_output; };
};
std::string NORMAL_STATE::getline(Generator *generator)
{
    std::string token = generator->getToken();
    if (token == "-a" || token == "--add")
        generator->setState(new ADD_STATE());
    else if (token == "-c" || token == "--copy")
        generator->setState(new COPY_STATE());
    else if (token == "-e" || token == "--env")
        generator->setState(new ENV_STATE());
    else if (token == "-f" || token == "--from")
        generator->setState(new FROM_STATE());
    else if (token == "-h" || token == "--help")
        generator->setState(new SKIP_STATE());
    else if (token == "-i" || token == "--ignore")
        generator->setState(new IGNORE_STATE());
    else if (token == "-m" || token == "--cmd")
        generator->setState(new CMD_STATE());
    else if (token == "-n" || token == "--entrypoint")
        generator->setState(new ENTRY_STATE());
    else if (token == "-o" || token == "--output")
        generator->setState(new SKIP_STATE());
    else if (token == "-p" || token == "--expose")
        generator->setState(new EXPOSE_STATE());
    else if (token == "-r" || token == "--run")
        generator->setState(new RUN_STATE());
    else
        generator->setState(new ERROR_STATE());
    return generator->getline();
}
std::string ADD_STATE::getline(Generator *generator)
{
    // Implementation for ADD_STATE
}
std::string COPY_STATE::getline(Generator *generator)
{
    // Implementation for COPY_STATE
}
std::string ENV_STATE::getline(Generator *generator)
{
    // Implementation for ENV_STATE
}
std::string FROM_STATE::getline(Generator *generator)
{
    // Implementation for FROM_STATE
}
std::string HELP_STATE::getline(Generator *generator)
{
    // Implementation for HELP_STATE
}
std::string IGNORE_STATE::getline(Generator *generator)
{
    // Implementation for IGNORE_STATE
}
std::string CMD_STATE::getline(Generator *generator)
{
    // Implementation for CMD_STATE
}
std::string ENTRY_STATE::getline(Generator *generator)
{
    // Implementation for ENTRY_STATE
}
std::string EXPOSE_STATE::getline(Generator *generator)
{
    // Implementation for EXPOSE_STATE
}
std::string RUN_STATE::getline(Generator *generator)
{
    // Implementation for RUN_STATE
}
std::string SKIP_STATE::getline(Generator *generator)
{
    // Implementation for SKIP_STATE
}
std::string ERROR_STATE::getline(Generator *generator)
{
    // Implementation for ERROR_STATE
}