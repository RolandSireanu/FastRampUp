#include <string>
#include <utility>
#include <iostream>
#include <cstddef>
#include <stack>
#include <memory>

class text final 
{

    public:
        text(std::string content = "") : content{move(content)}
        {

        }

        void insert(std::size_t const position, const std::string& sequence)
        {
            content.insert(position, sequence);
        }

        void erase(const std::size_t position, const std::size_t lenght)
        {
            content.erase(position, lenght);
        }

        std::string substr(const std::size_t position, const std::size_t length)
        {
            return content.substr(position, length);
        }


        friend std::ostream& operator<<(std::ostream& os, const text& arg) 
        {
            return (os<<arg.content);
        }

    private:
        std::string content;
};

class command 
{
    public:
        command(text& t): t{&t}
        {

        }

        virtual ~command() = default;
        virtual void apply() = 0;
        virtual void undo() = 0;


    protected:
        text* t;


};

class addition final : public command 
{
    public:

        addition(text& t, const std::size_t position, std::string sequence):
            command(t), position{position}, sequence{std::move(sequence)}
        {

        }

        void apply() final
        {
            t->insert(position, sequence);
        }

        void undo()
        {   
            t->erase(position, sequence.size());
        }

    private:
        std::size_t position;
        std::string sequence;
};

class deletion final : public command 
{
    public:

        deletion(text& t, const std::size_t position, std::size_t length):
            command(t), 
            position{position}, 
            target{t.substr(position, length)}
        {

        }

        void apply() final
        {
            t->erase(position, target.length());            
        }

        void undo()
        {               
            t->insert(position, target);
        }

    private:
        std::size_t position;
        std::string target;
};


class controller final 
{
    public:
        controller(text& t) : target{t}
        {

        }

        void insert(std::size_t position, std::string sequence)
        {
            apply<addition>(target, position, sequence);
        }

        void erase(std::size_t position, std::size_t length)
        {
            apply<deletion>(target, position, length);
        }

        void undo() 
        {
            applied.top()->undo();
            shift_elements(applied, undone);
            // undone.push(std::move(applied.top()));
            // applied.pop();
        }

        void redo()
        {
            undone.top()->apply();
            shift_elements(undone, applied);
        }

    private:
        using rep = std::stack<std::unique_ptr<command> >;
        text& target;
        rep applied;
        rep undone;

        template<typename T, typename ...Args>
        void apply(Args&& ...args)
        {
            auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
            applied.push(move(ptr));
            applied.top()->apply();
            undone = {};
        }

        void shift_elements(rep& source, rep& destination)
        {
            destination.emplace(std::move(source.top()));
            source.pop();
        }

};

int main()
{
    text t("Hello world !");
    t.insert(1,"A"); 
    t.insert(6," www");
    t.erase(1,1);
    std::cout << t.substr(0,5) << std::endl;
    std::cout << t << std::endl;

    text temp("Ana merge la munte dupa mere !");
    controller c(temp);
    c.insert(3," ,");
    c.erase(3,2);
    c.undo();
    c.redo();
    std::cout << temp << std::endl;

    return 0;
}
