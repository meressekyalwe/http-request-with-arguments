#include <iostream>
#include <string>
#include <cpr/cpr.h>

using namespace std;

void responseObjects(const cpr::Response& r)
{
    if(r.status_code == 0)
        cerr << r.error.message << endl;
    else if (r.status_code >= 400)
    {
        cerr << "Error [" << r.status_code << "] making request" << endl;
    } else
    {
        cout << "Request took " << r.elapsed << endl;
        cout << "Body:" << endl << r.text;
    }
}

int main()
{
    cpr::Response r;
    string name, value, command;
    cout << "name value command" << endl << ">>";
    std::cin >> name >> value >> command;

    if (command == "get")
    {
        string url = "http://httpbin.org/get";
        url += ("?" + name + "=" + value);
        r = cpr::Get(cpr::Url{url});
    }
    else if (command == "post")
    {
        r = cpr::Post(cpr::Url{"http://httpbin.org/post"}, cpr::Payload{{name.c_str(), value.c_str()}});
    }

    responseObjects(r);

    return 0;
}
