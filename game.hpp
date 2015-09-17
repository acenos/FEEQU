class game_data {

	public:
		int map_h;
		int map_w;
		int* map;

		game_data();
		~game_data();
		void new_map(int h, int w);

};
