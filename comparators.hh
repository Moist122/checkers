#pragma once

class Between{
public:
    bool operator()(char x, char y, char z) //check if x<=y<=z
        {return x<=y&&z>=y ? true:false;}
};