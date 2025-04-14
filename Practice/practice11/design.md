1. The Program
 The board game cafe management system is small application for tracking board game inventory and customer borrowing.
The program maintains a catalog of all board games with availability status, 
enabling staff to check out games to customers with due dates, and tracks when games are returned.
It helps  caffe staff to efficiently manage the lending part of the business by providing visibility into
current inventory status and borrowing records.
2. Nouns
 BoardGame: A game in cafe's collection
 Customer: A person who borrows
 Loan: A record of a game being borrowed
 Inventory: A collecttion of all the games in the inventory
 Copy: A physical instance of a game 

 addGame: A new game being added to inventory
 remove Game A game being removed from inventory
 checkOut: A lending process of a game to a customer
 returnGame: A game being returned
 dispplayAvailableGames: A collection of games in inventory being displayed 
 find Game: A search for a specific game
 calculateDueDate: Determine when a game should be returned

3. Possible Classes Structure:

    cppclass BoardGame {
    private:
        std::string title;
        std::string publisher;
        int minPlayers;
        int maxPlayers; 
        int playTimeMinutes;
        int totalCopies;
        int availableCopies;

    public:
        // Constructors
        BoardGame(std::string title, std::string publisher, int minPlayers, 
                int maxPlayers, int playTimeMinutes, int copies);
        
        // Getters
        std::string getTitle() const;
        std::string getPublisher() const;
        int getMinPlayers() const;
        int getMaxPlayers() const;
        int getPlayTimeMinutes() const;
        int getTotalCopies() const;
        int getAvailableCopies() const;
        
        // Operations
        bool isAvailable() const;
        void incrementAvailable();
        bool decrementAvailable();
    };

    class Customer {
    private:
        int id;
        std::string name;
        std::string email;
        std::string phone;
        
    public:
        // Constructors
        Customer(int id, std::string name, std::string email, std::string phone);
        
        // Getters
        int getId() const;
        std::string getName() const;
        std::string getEmail() const;
        std::string getPhone() const;
        
        // Setters
        void setEmail(const std::string& email);
        void setPhone(const std::string& phone);
    };

    class Loan {
    private:
        int loanId;
        BoardGame* game;
        Customer* customer;
        std::time_t checkoutDate;
        std::time_t dueDate;
        bool returned;
        std::time_t returnDate;
        
    public:
        // Constructors
        Loan(int loanId, BoardGame* game, Customer* customer, 
            int loanDurationDays = 7);
        
        // Getters
        int getLoanId() const;
        BoardGame* getGame() const;
        Customer* getCustomer() const;
        std::time_t getCheckoutDate() const;
        std::time_t getDueDate() const;
        bool isReturned() const;
        std::time_t getReturnDate() const;
        
        // Operations
        void returnGame();
        bool isOverdue() const;
        int daysOverdue() const;
    };

    class GameLibrary {
    private:
        std::vector<BoardGame> games;
        std::vector<Customer> customers;
        std::vector<Loan> loans;
        int nextLoanId;

    public:
        // Constructor
        GameLibrary();
        
        // Game operations
        void addGame(const BoardGame& game);
        void removeGame(const std::string& title);
        BoardGame* findGame(const std::string& title);
        std::vector<BoardGame> getAvailableGames() const;
        
        // Customer operations
        void addCustomer(const Customer& customer);
        Customer* findCustomer(int id);
        Customer* findCustomer(const std::string& name);
        
        // Loan operations
        Loan* checkOutGame(const std::string& gameTitle, int customerId);
        bool returnGame(int loanId);
        std::vector<Loan> getActiveLoans() const;
        std::vector<Loan> getOverdueLoans() const;
        std::vector<Loan> getLoansForCustomer(int customerId) const;
        
        // Display operations
        void displayInventory() const;
        void displayCustomers() const;
        void displayActiveLoans() const;
    };

Class Diagram:
mermaidclassDiagram
    class BoardGame {
        -string title
        -string publisher
        -int minPlayers
        -int maxPlayers
        -int playTimeMinutes
        -int totalCopies
        -int availableCopies
        +BoardGame(title, publisher, minPlayers, maxPlayers, playTimeMinutes, copies)
        +getTitle() string
        +getPublisher() string
        +getMinPlayers() int
        +getMaxPlayers() int
        +getPlayTimeMinutes() int
        +getTotalCopies() int
        +getAvailableCopies() int
        +isAvailable() bool
        +incrementAvailable() void
        +decrementAvailable() bool
    }
    
    class Customer {
        -int id
        -string name
        -string email
        -string phone
        +Customer(id, name, email, phone)
        +getId() int
        +getName() string
        +getEmail() string
        +getPhone() string
        +setEmail(email) void
        +setPhone(phone) void
    }
    
    class Loan {
        -int loanId
        -BoardGame* game
        -Customer* customer
        -time_t checkoutDate
        -time_t dueDate
        -bool returned
        -time_t returnDate
        +Loan(loanId, game, customer, loanDurationDays)
        +getLoanId() int
        +getGame() BoardGame*
        +getCustomer() Customer*
        +getCheckoutDate() time_t
        +getDueDate() time_t
        +isReturned() bool
        +getReturnDate() time_t
        +returnGame() void
        +isOverdue() bool
        +daysOverdue() int
    }
    
    class GameLibrary {
        -vector~BoardGame~ games
        -vector~Customer~ customers
        -vector~Loan~ loans
        -int nextLoanId
        +GameLibrary()
        +addGame(game) void
        +removeGame(title) void
        +findGame(title) BoardGame*
        +getAvailableGames() vector~BoardGame~
        +addCustomer(customer) void
        +findCustomer(id) Customer*
        +findCustomer(name) Customer*
        +checkOutGame(gameTitle, customerId) Loan*
        +returnGame(loanId) bool
        +getActiveLoans() vector~Loan~
        +getOverdueLoans() vector~Loan~
        +getLoansForCustomer(customerId) vector~Loan~
        +displayInventory() void
        +displayCustomers() void
        +displayActiveLoans() void
    }
    
    Loan "0..*" --> "1" BoardGame: borrows
    Loan "0..*" --> "1" Customer: borrowed by
    GameLibrary "1" --> "0..*" BoardGame: contains
    GameLibrary "1" --> "0..*" Customer: registers
    GameLibrary "1" --> "0..*" Loan: manages