#include <iostream>
#include <memory>
#include <string>

using namespace std;

class DataElement;

class Visitor
{
    public:
        virtual void visitDataElement(shared_ptr<DataElement> data_element) = 0;
};

class Element : public enable_shared_from_this<Element>
{
    public:
        virtual void accept(shared_ptr<Visitor> visitor) = 0;
};

class DataElement : public Element
{
    private:
        string name_;
        int age_;
    public:
        DataElement(string name, int age) : name_(name), age_(age) {}
        void accept(shared_ptr<Visitor> visitor) override
        {
            visitor->visitDataElement(dynamic_pointer_cast<DataElement>(this->shared_from_this()));
        }
        string getDataInfomation()
        {
            return name_ + " is " + to_string(age_) + " years old.";
        }
};            

class PDFVisitor : public Visitor
{
    public:
        void visitDataElement(shared_ptr<DataElement> data_element) override
        {
            auto info = data_element->getDataInfomation();
            cout << "Export to pdf format: " << info << endl;
        }
};

class CSVVisitor : public Visitor
{
    public:
        void visitDataElement(shared_ptr<DataElement> data_element) override
        {
            auto info = data_element->getDataInfomation();
            cout << "Export to csv format: " << info << endl;
        }
};

void clientTest()
{
    auto pdf_visitor = make_shared<PDFVisitor>();
    auto csv_visitor = make_shared<CSVVisitor>();
    auto data = make_shared<DataElement>("Ryannnnn", 26);
    // export data
    data->accept(pdf_visitor);
    data->accept(csv_visitor);
}

int main()
{
    clientTest();
    return 0;
}

