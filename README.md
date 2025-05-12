# Chase hit monster
-
# GIỚI THIỆU GAME 
Chase hit monster là một game làm từ sdl2 đơn giản với nội dung chính là nhân vật di chuyển trên map tạo sẵn bắn những con quái vật xuất hiện ngẫu nhiên
# 1. BẮT ĐẦU GAME
Chờ một chút màn hình sẽ hiện ra màn hình start yêu cầu người chới phải bấm enter để bắt đầu 
![Screenshot 2025-05-12 112450](https://github.com/user-attachments/assets/c3c5c0c0-7eaf-4a29-a6ef-8fcf78bfc39e)
Sau khi bấm enter game sẽ hiện ra một màn hình
![Screenshot 2025-04-26 053544](https://github.com/user-attachments/assets/b869b76a-e23a-4e60-905f-9bd3e14c4f65)
# 2. CÁCH GAME HOẠT ĐỘNG
Nhân vật sẽ được di chuyển bằng các phím mũi tên hướng lên trên là nhảy, hướng sang trái là di chuyển sáng trái,hướng sang phải là di chuyển sang phải
Nhân vật bắn đạn bằng cách bấm phím space
![image](https://github.com/user-attachments/assets/9bd8c9b0-fd07-4953-83fb-0489509425f9)
khi người chơi di chuyển để quái chạm vào nhân vật thì ngay lập tức sẽ hiện ra màn hình Game Over và người chơi sẽ bị xử thua
![Screenshot 2025-05-12 112513](https://github.com/user-attachments/assets/1e345f0a-3154-4dfb-bab9-dac6c222609c)
# 3. CÁCH CHIẾN THẮNG
khi người chơi đưa được nhân vật đến phần cuối của bản đồ chạm vào lá cờ màu đỏ thì người chơi sẽ chiến thắng 
![Screenshot 2025-05-12 113011](https://github.com/user-attachments/assets/969e4de7-ab21-4344-947c-a81de8f8a8c5)
![Screenshot 2025-05-12 112603](https://github.com/user-attachments/assets/f2b85998-f834-4d04-ab23-873cd86f6002)
# Về đồ hoạ game 
- .png là để lấy ảnh trong suốt
- .ttf là font chữ để hiện bảng thông báo start
- .text đây là bảng tile với mỗi số tượng trưng cho 1 hình ảnh vdu dất cỏ dùng để tạo map di chuyển cho nhân vật
- các file ảnh được tìm trên ytb
# Về code game
- Chứa sdl2 sdl_ttf sdl_image dùng để tải ảnh tải chữ
- Map:dùng kĩ thuật tile map để tạo map vs mỗi 1 tile tượng trưng cho một hình ảnh
- bulet: đạn bắn ra từ nhân vật
- camera: dùng camera cuộn để có thể di chuyển map theo nhân vật
- enermy: quái vật mang hình dáng zombie được tạo ngẫu nhiên di chuyển theo hướng nhân vật
- player: nhân vật chính do người chơi điều khiển  
# Video
https://drive.google.com/file/d/1nL7pQYQ1JDlXxP3xgYINewhnXvnJAWAC/view?usp=sharing

