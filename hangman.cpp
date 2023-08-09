#include <iostream>
#include <random>  
#include <string>
#include <vector>



class Hangman final 
{
    const unsigned int maximum_number_of_tries = 7;                     

public:
    explicit Hangman(const std::vector<std::string>& words) :           
        m_random_generator{ std::random_device{}() },                   
        m_distribution{ 0, words.size() - 1 },                         
        m_word_number{ m_distribution(m_random_generator) },
        m_secret_word{ words[m_word_number] },                          
        m_guess_word{ std::string(m_secret_word.length(),'_') },      
        m_try_no{ 0u }                                                
    {
    }

    // todo : document
    void play()
    {
        bool won{ false };
        bool lost{ false };

        std::cout << "Welcome to Hangman plz save bob!\n";


        while (!won && !lost)
        {
            show_state();
            auto guess = make_guess();              
            handle_guess(guess);                   
            won = check_win();                      
            if (!won) lost = check_loss();
        }
    }

private:

    static char make_guess()
    {
        char c;
        std::cout << "\nEnter your guess:\n";
        std::cin >> c;

        return c;
    }

    void show_state() const                                             
    {
        std::cout << "\n\n";
        std::cout << m_hangman_art[m_try_no] << "\n";
        std::cout << m_guess_word << "\n";
    }

    void handle_guess(char guess)
    {
        if (m_secret_word.find(guess) != std::string::npos)
        {
            for (std::size_t i = 0; i < m_guess_word.length(); ++i) // changed int to size_t
            {
                if (m_secret_word[i] == guess)
                {
                    m_guess_word[i] = guess;
                }
            }
        }
    
        // increase try number
        ++m_try_no;
    }

    bool check_win() const
    {
        if (m_secret_word != m_guess_word) return false;
    
        std::cout << m_hangman_art[m_try_no] << "\n";
        std::cout << m_guess_word << "\n";
        std::cout << "You win! The word was " << m_secret_word << "\n";
        return true;
    }

    bool check_loss() const
    {
        if (m_try_no < maximum_number_of_tries) return false;           

        std::cout << m_hangman_art[m_try_no] << "\n";
        std::cout << m_guess_word << "\n";
        std::cout << "You lost! The word was " << m_secret_word << "\n";
        return true;
    }

    std::mt19937 m_random_generator;
    std::uniform_int_distribution<std::size_t> m_distribution;
    std::size_t m_word_number;
    std::string m_secret_word;
    std::string m_guess_word;
    unsigned int m_try_no;

    const std::string m_hangman_art[8] = {
        " +---+\n"
        " |   |\n"
        "     |\n"
        "     |\n"
        "     |\n"
        "     |\n"
        "==========",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "     |\n"
        "     |\n"
        "     |\n"
        "==========",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        " |   |\n"
        "     |\n"
        "     |\n"
        "==========",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "/|   |\n"
        "     |\n"
        "     |\n"
        "==========",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "/|\\  |\n"
        "     |\n"
        "     |\n"
        "==========",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "/|\\  |\n"
        "/    |\n"
        "     |\n"
        "==========",
        " +---+\n"
        " |   |\n"
        " O   |\n"
        "/|\\  |\n"
        "/ \\  |\n"
        "     |\n"
        "==========",
        "  +---+\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "O-<-< |\n"
        "==========",
    };
};


int main(){
    const std::vector<std::string> words = { "manhang", "hangman", "namgnah" };
    Hangman game{ words };
    game.play();
    return 0;
}
