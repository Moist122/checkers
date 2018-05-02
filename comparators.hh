#pragma once

class Between{
public:
    bool operator()(char x, char y, char z) 
    {return x<=y&&z>=y ? true:false;}
};

template <typename V>
class Different{
public:
    bool operator()(V x, V y)
        {return x!=y ? true:false;}
};