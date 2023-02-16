#include <cstddef> // for std::size_t
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <utility> //for std::move, std::forward
#include <vector>


//xml_node_base is the base class all XML node types
//output() is a non-virtual const function that always calls the do_output_*() functions with the stream passed to it.
// OOP requires the use of pointers, the xml_node_base_t type alias is defined to be std::shared_ptr<xml_node_base> so that all pointers are managed 

class xml_node_base
{
public:
    virtual ~xml_node_base() = default;
//
    void output(std::ostream &os) const
    {
        do_output_open(os); //
        do_output_body(os);
        do_output_close(os);
    }

protected:
    virtual void do_output_open(std::ostream &os) const = 0;
    virtual void do_output_body(std::ostream &) const {}
    virtual void do_output_close(std::ostream &os) const = 0;
};

using xml_node_base_t = std::shared_ptr<xml_node_base>;
using xml_node_bases_t = std::vector<xml_node_base_t>;

template <typename T, typename... Args>
inline xml_node_base_t make_xml_node(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

class xml_node : virtual public xml_node_base // xml_node class is publicly inheriting virtual from class xml_node_base
{
private:
    std::string nname;

public:
    xml_node() = delete;
    xml_node(std::string const &name) : nname{name}
    {
    }

protected:
    void do_output_open(std::ostream &os) const override
    {

        os << "<" << nname << ">";
    }
    void do_output_close(std::ostream &os) const override
    {

        // os << </name>;
        os << "</" << nname << ">";
    }

}; // End class xml_node

class xml_node_with_children : public xml_node
{

private:
    xml_node_bases_t children_;

public:
    xml_node_with_children() = delete;
    xml_node_with_children(std::string const &name) : xml_node{name}
    {
    }
    xml_node_with_children(std::string const &name, std::size_t reserve) : xml_node_with_children{name}
    {
        children_.reserve(reserve);
    }

    xml_node_with_children(std::string const &name, xml_node_bases_t children) : xml_node{name},
                                                                                 children_{std::move(children)} {};

protected:
    auto &children() { return children_; };
    auto const &children() const { return children_; };
    void do_output_body(std::ostream &os) const override
    {
        for (auto const &Ele : children_)
        {
            Ele->output(os);
        }
    }

}; // End class xml_node_with_children

template <typename T>
class value_node : public xml_node
{

private:
    T datum;

protected:
    void do_output_body(std::ostream &os) const override
    {
        os << datum;
    }

public:
    value_node(std::string const &name, T const &v) : xml_node{name}, datum(v)
    {
    }
}; // End value_node<T>

class note : public xml_node_with_children
{
public:
    note() = delete;
    // ~note();
    note(std::string const &to, std::string const &from, std::string const &subject, std::string const &message) : xml_node_with_children{"note", 4}
    {
        children().push_back(make_xml_node<value_node<std::string>>("to", to));
        children().push_back(make_xml_node<value_node<std::string>>("from", from));
        children().push_back(make_xml_node<value_node<std::string>>("subject", subject));
        children().push_back(make_xml_node<value_node<std::string>>("message", message));
    }
}; // End class note

class root : protected xml_node_with_children
{ // class root & std::ostream Operator

public:
    using xml_node_with_children::children;
    using xml_node_with_children::output;
    using xml_node_with_children::xml_node_with_children;
}; // End class root

std::ostream &operator<<(std::ostream &os, root const &r)
{
    r.output(os);
    return os;
}

//**** FUNCTION MAIN START ****//
int main()
{
    root notes{"notes"};
    notes.children().push_back(
        make_xml_node<note>("Joe", "UPS", "Reminder", "Pick up your package!"));
    notes.children().push_back(
        make_xml_node<value_node<double>>("priority", 54.23));
    std::cout << notes << '\n';
} // END OF FUNCITON MAIN