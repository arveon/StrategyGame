/* code is used to manipulate pixels on the texture
bg - SDL_Texture*
Uint32* pixels;
//getting the width and height of the texture if unknown
int w;
int h;
SDL_QueryTexture(bg, NULL, NULL, &w, &h);

int pitch = 0;//not used, SDL_LockTexture will try to write into 0x0000 address causing an exception
SDL_LockTexture(bg, NULL, reinterpret_cast<void**>(&pixels), &pitch); //need to do reinterpret_cast as it only accepts void** arguments
memset(pixels, 100, w * h * sizeof(Uint32)); //setting the values in the memory starting from pixels and finishing at pixels + (w*h*sizeof(Uint32)) to 255
SDL_UnlockTexture(bg); //unlock the texture so it can be rendered(?)
*/

//another way of getting file info and checking if its a folder
/*struct stat info;
if (stat(constants::SAVES_PATH.c_str(), &info) == 0)
{
if (info.st_mode & S_IFDIR)
{*/