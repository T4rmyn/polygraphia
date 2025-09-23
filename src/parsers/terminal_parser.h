#ifndef TERMINALPARSER_H
#define TERMINALPARSER_H

#include "parser.h"
#include "../mediator/mediator.h"
#include "../mediator/mediator.h"
#include <optional>
#include <iostream>


class TerminalParser: public BaseParser {
    public:
        void process_tokens(deque<string> *tokens) override;
};

#endif 