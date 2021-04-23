/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
/*
 * Part of the DeamerProject.
 * For more information go to: https://github.com/Deruago/theDeamerProject
 */

#ifndef DEAMER_FILE_TOOL_OSTYPE_H
#define DEAMER_FILE_TOOL_OSTYPE_H

namespace deamer::file::tool
{
	enum class OSType
	{
		unknown,
		all,
		os_linux,
		os_windows,
		os_mac,
	};

#if defined(__linux__) || defined(linux) || defined(unix) || defined(__unix__)
	constexpr static OSType os_used = OSType::os_linux;
#elif defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	constexpr static OSType os_used = OSType::os_windows;
#elif defined(__APPLE__) || defined(__MACH__)
	constexpr static OSType os_used = OSType::os_mac;
#else
	constexpr static OSType os_used = OSType::unknown;
#endif
}

#endif // DEAMER_FILE_TOOL_OSTYPE_H
