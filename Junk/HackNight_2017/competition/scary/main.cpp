#include <iostream>

int main()
{
	int x = 0;
	int v_h = 0;
	int v_t = 0;
	int n = 0;
	int k = 0;

	std::cin >> x >> v_h >> v_t >> n >> k;

	bool resting = false;
	bool warping = true;
	int hero_pos = 0;
	int scary_pos = v_t*2*k;
	int  warps = 0;
	int energy = n;

	while (hero_pos < x)
	{
		if(!resting)
		{
			energy--;
			hero_pos += v_h;
			if(energy == 0)
			{
				resting = true;
			}
		}
		else
		{
			resting = false;
			energy = n;
		}


		if(warping)
		{
			scary_pos -= 2*v_t;
			if(scary_pos <=0)
			{
				scary_pos = 0;
				warping = false;
			}
		}
		else
		{
			scary_pos += v_t;
			if(scary_pos >= hero_pos)
			{
				warping = true;
				warps++;
			}
		}
	}
	std::cout << warps;
}
