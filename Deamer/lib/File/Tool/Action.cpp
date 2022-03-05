#include "Deamer/File/Tool/Action.h"
#include "Deamer/File/Tool/Action/Builder.h"

deamer::file::tool::Action::Action(std::string action_) : action(std::move(action_))
{
}

const std::string& deamer::file::tool::Action::GetAction() const
{
	return action;
}

std::string deamer::file::tool::Action::GetSubShellAction(const file::tool::OSType os,
														  const std::string& directory) const
{
	switch (os)
	{
	case file::tool::OSType::unknown:
	case file::tool::OSType::all:
	case file::tool::OSType::os_linux:
		return "( cd " + directory + " ; " + GetAction() + " )";
	case file::tool::OSType::os_windows:
		return "bash -c \"( cd " + directory + " ; " + GetAction() + " )\"";
	case file::tool::OSType::os_mac:
		return "( cd " + directory + " ; " + GetAction() + " )";
	}

	throw std::logic_error("Unknown os given");
}

std::unique_ptr<deamer::file::tool::action::Action>
deamer::file::tool::Action::GetGeneralAction() const
{
	auto builder = action::Builder();
	builder.CrossPlatformCommand(GetAction());
	auto generalAction = builder.GetAction();
	return generalAction;
}
