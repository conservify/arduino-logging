#include "test_logging.h"

LoggingSuite::LoggingSuite() {
}

LoggingSuite::~LoggingSuite() {
};

class Example {
public:
    friend LogStream& operator<<(LogStream &log, const Example &example) {
        return log << "Example<>";
    }
};

static size_t LogMessageHook(const LogMessage *m, const char *formatted, void *arg) {
    std::vector<std::string> *messages = (std::vector<std::string> *)arg;
    messages->emplace_back(formatted);
    return 0;
}

void LoggingSuite::SetUp() {
    log_add_hook(LogMessageHook, (void *)&messages);
    log_configure_time(nullptr, nullptr);
};

void LoggingSuite::TearDown() {
    log_add_hook(nullptr, nullptr);
};

TEST_F(LoggingSuite, Simple) {
    logf(LogLevels::INFO, "Simple", "Hello World");

    EXPECT_EQ(messages.size(), 1);
    EXPECT_EQ(messages[0], "000000 Simple                    Hello World\n");
}

TEST_F(LoggingSuite, DisableHook) {
    logf(LogLevels::INFO, "Simple", "Hello World");

    log_configure_hook(false);

    logf(LogLevels::INFO, "Simple", "Bye World");

    EXPECT_EQ(messages.size(), 1);
    EXPECT_EQ(messages[0], "000000 Simple                    Hello World\n");
}

TEST_F(LoggingSuite, LogStream) {
    Logger logger("Root");
    logger() << "Hello" << " " << "World";

    logger() << "Hello" << " " << "World " << 100 << " " << 3.14;

    EXPECT_EQ(messages.size(), 2);
    EXPECT_EQ(messages[0], "000000 Root                      Hello World\n");
    EXPECT_EQ(messages[1], "000000 Root                      Hello World 100 3.140000\n");

    auto example = Example{};
    logger() << "Hello" << " " << example;
    EXPECT_EQ(messages.size(), 3);
    EXPECT_EQ(messages[2], "000000 Root                      Hello Example<>\n");

    logger.begin() << "Hello " << example;
    EXPECT_EQ(messages.size(), 4);
    EXPECT_EQ(messages[3], "000000 Root                      Hello Example<>\n");

    logger() << "Hello " << example;
    EXPECT_EQ(messages.size(), 5);
    EXPECT_EQ(messages[4], "000000 Root                      Hello Example<>\n");
}

TEST_F(LoggingSuite, EmptyMessage) {
    Logger logger("Root");

    logger() << "";

    EXPECT_EQ(messages.size(), 1);
    EXPECT_EQ(messages[0], "000000 Root                      \n");
}

TEST_F(LoggingSuite, TooLongMessage) {
    Logger logger("Root");
    {
        auto e = logger.begin();
        for (auto i = 0; i < 60 ; ++i) {
            e << "Jacob";
        }
    }

    EXPECT_EQ(messages.size(), 1);
    EXPECT_EQ(messages[0], "000000 Root                      JacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJacobJac\n");
}
