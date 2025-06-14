from playwright.sync_api import sync_playwright
import os
import time
import json
import subprocess
# subprocess.Popen([
#     r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
#     "--remote-debugging-port=666",
#     '--user-data-dir=D:\playwright_chrome'
# ])

# time.sleep(2)  # Wait for Edge to start and open the debugging port



with sync_playwright() as p:
    browser = p.chromium.connect_over_cdp("http://localhost:666")
    page = browser.new_page()
    page.goto("https://gaokao.chsi.com.cn/zyk/pub/appraisalinfo/1", wait_until="networkidle")
    page.wait_for_selector("body")  # 等待页面加载

    # 假设页面直接返回的是json内容
    try:
        json_data = page.evaluate("() => JSON.parse(document.body.innerText)")
        print(json_data)
    except Exception as e:
        print("无法解析为JSON:", e)

# p = sync_playwright().start()
# # browser = p.chromium.launch(channel="msedge", headless=False)
# browser = p.chromium.connect_over_cdp("http://localhost:666")
# page = browser.new_page()
# page.goto("https://gaokao.chsi.com.cn/")
# input()
# print(page.title())
# print(page.content())
# input()

