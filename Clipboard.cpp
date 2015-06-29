#include "Clipboard.h"

Clipboard::Clipboard():mem("")
{
}

void Clipboard::put(string str)
{
    this->mem=str;
}

string Clipboard::get()
{
    return this->mem;
}
