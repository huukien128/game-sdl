# Cosmic Shooter

## Thông tin sinh viên

- **Họ tên:** Nguyễn Hữu Kiên  
- **Mã sinh viên:** 24022807

 ## Giới thiệu chủ đề game

Cosmic Shooter là một trò chơi bắn súng không gian 2D được lập trình bằng C++ sử dụng thư viện SDL2. Trong game, người chơi điều khiển một phi thuyền chiến đấu chống lại các đợt tấn công của kẻ địch trong không gian. Trò chơi có hệ thống điểm số, lưu high score, chuyển màn, menu điều khiển và hiệu ứng âm thanh sống động.


## Ngưỡng điểm đề xuất **8.0** điểm.


## Lý do bảo vệ ngưỡng điểm 8.0

- Hoàn thiện đầy đủ chức năng cơ bản: Di chuyển, bắn đạn, tiêu diệt kẻ địch, kết thúc game khi người chơi bị trúng bom.
- Có menu và hướng dẫn cách chơi: Giao diện menu gồm các lựa chọn "Start Game", "How to Play", "Exit Game".
- Hiển thị điểm số và high score: Điểm số được cập nhật liên tục và high score được lưu lại qua các lần chơi.
- Cấu trúc mã nguồn rõ ràng: Mã nguồn được chia thành các file riêng biệt như `Player`, `Enemy`, `Bullet`, `Menu`, `Game`, `TextureManager`, v.v.
- Có tính mở rộng: Game có hệ thống level và độ khó tăng theo thời gian.
- Tích hợp âm thanh cơ bản: Có hiệu ứng khi bắn, nổ, và nhạc nền đơn giản.


## Tính năng chính

- Điều khiển phi thuyền di chuyển và bắn đạn
- Kẻ địch di chuyển ngẫu nhiên, tấn công bằng bom 
- Hệ thống cấp độ: tăng độ khó theo thời gian
- Điểm số và high score được lưu lại
- Giao diện menu chính: Start Game, How to Play, Exit
- Hiệu ứng âm thanh và đồ họa sinh động

## Yêu cầu hệ thống

- Hệ điều hành: Windows (khuyến nghị), hoặc Linux
- Phần mềm: Code::Blocks (hoặc IDE khác hỗ trợ C++)
- Thư viện: SDL2, SDL2_image, SDL2_ttf, SDL2_mixer

## Hướng dẫn cài đặt và chạy (Windows + Code::Blocks)

1. Tải và cài đặt:
   - [SDL2](https://www.libsdl.org/)
   - SDL2_image, SDL2_ttf, SDL2_mixer

2. Mở Code::Blocks và tạo project mới, thêm toàn bộ file `.cpp` và `.h` từ thư mục vào project.

3. Cấu hình đường dẫn:
   - **Search directories** → thêm thư mục chứa SDL2/include
   - **Linker settings** → thêm các thư viện:
     ```
     SDL2
     SDL2_image
     SDL2_ttf
     SDL2_mixer
     ```

4. Build và chạy chương trình (F9)

## Cách chơi

- **Di chuyển**: Phím mũi tên
- **Bắn đạn**: Phím Space
- **Tránh bom/kẻ địch**: Né tránh để không mất mạng
- **Mục tiêu**: Ghi điểm cao nhất có thể

## Cấu trúc game

| Thư mục/File               | Mô tả                        |
|----------------------------|------------------------------|
| `Font `                    | Chứa font chữ (TTF)          |
| `image `                   | Chứa ảnh (nhân vật, đạn, nền, enemy...) |
| `sound `                   | Chứa âm thanh và nhạc nền    |
| `highscore1.txt`           | Lưu điểm cao nhất            |
| `SDL2.dll`                 | Thư viện SDL2 (bắt buộc)     |
| `SDL2_image.dll`           | Thư viện xử lý ảnh           |
| `SDL2_mixer.dll`           | Thư viện xử lý âm thanh      |
| `SDL2_ttf.dll`             | Thư viện xử lý font chữ      |
| `Bomb.cpp / .h`            | Quản lý bom                  |
| `Bullet.cpp / .h`          | Quản lý đạn                  |
| `Enemy.cpp / .h`           | Quản lý kẻ địch              |
| `FontManager.cpp / .h`     | Quản lý font chữ             |
| `Game.cpp / .h`            | Logic chính của game        |
| `Menu.cpp / .h`            | Menu chính                   |
| `Player.cpp / .h`          | Người chơi                   |
| `SoundManager.cpp / .h`    | Quản lý âm thanh             |
| `TextureManager.cpp / .h`  | Quản lý texture ảnh         |
| `main.cpp`                 | Hàm chính chạy game          |
| `README.md`                | File hướng dẫn               |
| `cosmic-shooter.cbp`       | Dự án Code::Blocks           |
