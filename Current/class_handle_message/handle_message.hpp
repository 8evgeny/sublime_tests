#ifndef HANDLE_MESSAGE_HPP
    #define HANDLE_MESSAGE_HPP

    #include "memory"
    #include <iostream>
    #include "thread"

    class handleMessage
    {
    public:
        // Static method to access the handleMessage instance
        static handleMessage & getInstance()
        {
            // If the instance doesn't exist, create it
            if (!instance_ptr)
            {
                instance_ptr = new handleMessage();
            }
            return * instance_ptr;
        } // END getInstance()

        // Delete the copy and move constructor and assignment operator
        handleMessage(const handleMessage &) = delete;
        handleMessage& operator=(const handleMessage &) = delete;
        handleMessage(const handleMessage &&) = delete;

        void operation1();
        void operation2();
        void operation3();

    private:
        // Private constructor to prevent external instantiation
        handleMessage();
        // Private destructor to prevent external deletion
        ~handleMessage();
        // Private static instance variable
        static handleMessage* instance_ptr;

    }; // END class handleMessage

#endif // HANDLE_MESSAGE_HPP


