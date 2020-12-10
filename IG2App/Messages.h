#pragma once

enum MessageType { flipFace, unflipFace};

struct Messages
{
	MessageType message;
};

struct FlipMessage : Messages
{
	FlipMessage(){
		message = flipFace;
	}
};

struct UnFlipMessage : Messages
{
	UnFlipMessage() {
		message = unflipFace;
	}
};
