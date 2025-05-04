# Cosmic Shooter

Cosmic Shooter là một trò chơi bắn súng không gian 2D được lập trình bằng C++ sử dụng thư viện SDL2. Trong game, người chơi điều khiển một phi thuyền chiến đấu chống lại các đợt tấn công của kẻ địch trong không gian. Trò chơi có hệ thống điểm số, lưu high score, chuyển màn, menu điều khiển và hiệu ứng âm thanh sống động.

## Thông tin sinh viên

- **Họ tên:** Nguyễn Hữu Kiên  
- **Mã số sinh viên:** 24022807  

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
     SDL2main
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



