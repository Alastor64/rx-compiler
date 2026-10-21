class A {
  public:
    virtual ~A() {}
};
class B {};
int main() {
    A *a = nullptr;
    B *b = dynamic_cast<B *>(a);
    return 0;
}