using namespace std;
#include <string>
//todo: static assert to force the implementation of methods
//this is crtp like, but also creates vtables as runtime polymorphism makes the code smaller
template <typename Derive, typename val_type>
class LitExp
{
    private:
        const string expStr;
        val_type val;
        //     const inline  virtual string toStr() const = 0;
    public:
        virtual inline val_type getVal() const = 0;
        virtual const val_type &add(LitExp *b) = 0;

        // const inline string getExpStr() const { return expStr; }
        // friend ostream &operator<<(ostream &os, const Expr &expr);
    protected:
        virtual Derive* is_compatible(LitExp *b) = 0;
        LitExp() = default; //prohibiting creation of Litexps, as shown in the documentation
};