#ifndef MOD_TEXTURE_HPP
#define MOD_TEXTURE_HPP

struct physical_device;
struct device;

struct texture {
	buffer tbuf;
	image img;
};

void texture_create(texture *tex, const device &dev, const physical_device &gpu, const std::string &path);

void texture_destroy(const texture &tex, const device &dev);

#endif
