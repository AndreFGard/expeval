using namespace std;
#include <string>
template <typename Derive, typename val_type>
class LitExp
{
    private:
        const string expStr;
        val_type val;
        //     const inline  virtual string toStr() const = 0;
    public:
        virtual inline val_type getVal() const;
        virtual const val_type &add(LitExp *b);

        // const inline string getExpStr() const { return expStr; }
        // friend ostream &operator<<(ostream &os, const Expr &expr);
    protected:
        virtual Derive* is_compatible(LitExp *b);
        LitExp() = default; //prohibiting creation of Litexps, as shown in the documentation
};