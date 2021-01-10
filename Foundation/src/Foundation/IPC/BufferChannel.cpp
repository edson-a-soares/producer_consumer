#include "Foundation/IPC/BufferChannel.h"

namespace Foundation {
namespace IPC {


	const int BufferChannel::CHANNEL_LENGTH         = 25 * 1024;
	const std::string BufferChannel::INPUT_CHANNEL  = "__INPUT_CHANNEL__";
    const std::string BufferChannel::OUTPUT_CHANNEL = "__OUTPUT_CHANNEL__";


} }
