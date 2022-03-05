#include "Deamer/File/Tool/Action/Action.h"
#include "Deamer/File/Tool/Action/Builder.h"
#include <gtest/gtest.h>

class TestAction : public testing::Test
{
protected:
	TestAction() = default;
	virtual ~TestAction() = default;

protected:
};

TEST_F(TestAction, ChangeDirectory_LinuxPython_CorrectCommand)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_linux);
	builder.ChangeDirectory("./other_directory");
	const auto action = builder.GetAction();
	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS linux" "any CD \"./\"" "any CD \"./other_directory\""))";

	EXPECT_EQ(expected_command, action->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}

TEST_F(TestAction, ChangeDirectory_WindowsPython_CorrectCommand)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_windows);
	builder.ChangeDirectory("./other_directory");
	const auto action = builder.GetAction();
	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS windows" "any CD \"./\"" "any CD \"./other_directory\""))";

	EXPECT_EQ(expected_command, action->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}

TEST_F(TestAction, ChangeDirectory_LinuxLinux_CorrectCommand)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_linux);
	builder.ChangeDirectory("./other_directory");
	const auto action = builder.GetAction();
	const std::string expected_command = R"((cd "./" ; cd "./other_directory"))";

	EXPECT_EQ(
		expected_command,
		action->ConstructArgument(deamer::file::tool::action::CommandTarget::os_linux, "./", true));
}

TEST_F(TestAction, ChangeDirectory_WindowsWindows_CorrectCommand)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_windows);
	builder.ChangeDirectory("./other_directory");
	const auto action = builder.GetAction();
	const std::string expected_command = R"((cd "./" && cd "./other_directory"))";

	EXPECT_EQ(expected_command,
			  action->ConstructArgument(deamer::file::tool::action::CommandTarget::os_windows, "./",
										true));
}

TEST_F(TestAction, MoveFile_LinuxPython_CorrectCommand)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_linux);
	builder.MoveFile("./other_directory1", "./other_directory2");
	const auto action = builder.GetAction();
	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS linux" "any CD \"./\"" "any MOVEFILE \"./other_directory1\" \"./other_directory2\""))";

	EXPECT_EQ(expected_command, action->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}

TEST_F(TestAction, RemoveFile_LinuxPython_CorrectCommand)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_linux);
	builder.RemoveFile("./other_directory");
	const auto action = builder.GetAction();
	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS linux" "any CD \"./\"" "any REMFILE \"./other_directory\""))";

	EXPECT_EQ(expected_command, action->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}

TEST_F(TestAction, MoveFile_WindowsPython_CorrectCommand)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_windows);
	builder.MoveFile("./other_directory1", "./other_directory2");
	const auto action = builder.GetAction();
	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS windows" "any CD \"./\"" "any MOVEFILE \"./other_directory1\" \"./other_directory2\""))";

	EXPECT_EQ(expected_command, action->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}

TEST_F(TestAction, RemoveFile_WindowsPython_CorrectCommand)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_windows);
	builder.RemoveFile("./other_directory");
	const auto action = builder.GetAction();
	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS windows" "any CD \"./\"" "any REMFILE \"./other_directory\""))";

	EXPECT_EQ(expected_command, action->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}

TEST_F(TestAction, CopyAction_ActionIsCorrectlyCopied)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_linux);
	builder.ChangeDirectory("./other_directory");

	const auto action = builder.GetAction();
	const auto actionCopy = action->Copy();

	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS linux" "any CD \"./\"" "any CD \"./other_directory\""))";

	EXPECT_FALSE(action->IsEmpty());
	EXPECT_FALSE(actionCopy->IsEmpty());
	EXPECT_EQ(expected_command, action->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
	EXPECT_EQ(expected_command, actionCopy->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}

TEST_F(TestAction, DoubleCopyAction_ActionIsCorrectlyCopied)
{
	auto builder = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_linux);
	builder.ChangeDirectory("./other_directory");

	const auto action = builder.GetAction();
	const auto actionCopy = action->Copy();
	const auto actionCopyCopy = actionCopy->Copy();

	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS linux" "any CD \"./\"" "any CD \"./other_directory\""))";

	EXPECT_FALSE(action->IsEmpty());
	EXPECT_FALSE(actionCopy->IsEmpty());
	EXPECT_FALSE(actionCopyCopy->IsEmpty());
	EXPECT_EQ(expected_command, action->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
	EXPECT_EQ(expected_command, actionCopy->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
	EXPECT_EQ(expected_command, actionCopyCopy->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}

TEST_F(TestAction, AddAction_ActionIsCorrectlyAdded)
{
	auto builder1 = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_linux);
	builder1.ChangeDirectory("./other_directory1");
	auto builder2 = deamer::file::tool::action::Builder(deamer::file::tool::OSType::os_linux);
	builder2.ChangeDirectory("./other_directory2");

	const auto action1 = builder1.GetAction();
	const auto action2 = builder2.GetAction();

	*action1 += *action2;

	const std::string expected_command =
		R"((python3 ./ "SETTING OUR_OS linux" "any CD \"./\"" "any CD \"./other_directory1\"" "any CD \"./other_directory2\""))";

	EXPECT_FALSE(action1->IsEmpty());
	EXPECT_EQ(expected_command, action1->ConstructArgument(
									deamer::file::tool::action::CommandTarget::python, "./", true));
}
