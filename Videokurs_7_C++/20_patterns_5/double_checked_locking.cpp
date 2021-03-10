Singleton* Singleton::m_instance;
bool Singleton::m_instance_guard; // false
std::mutex Singleton::m_mutex;

Singleton* Singleton::getInstance()
{
    // if (!m_instance_guard) {
    // if (!m_instance) {
        // std::lock_guard<std::mutex> lock(m_mutex);
        // if (!m_instance_guard) {
        if (m_instance == nullptr) {
            // m_instance_guard = true;
            m_instance = new Singleton;
        }
    }
    return m_instance;
}

Singleton* Singleton::getInstance()
{
    static Singleton m_instance;
    return &m_instance;
}
